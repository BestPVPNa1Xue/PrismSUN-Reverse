#include "clock_chain.hpp"
#include <algorithm>
#include <cerrno>
#include <chrono>
#include <limits>
#include <stdexcept>
#include <system_error>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <bcrypt.h>
#else
#include <cstdlib>
#include <time.h>
#include <unistd.h>
#endif

namespace prism::clockchain {
ClockValue timestamp(Services& svc) {
    // 0x140c9c. No differences between clocks are computed.
    for(int id:{4,1,2,3}) if(auto t=svc.clock_gettime(id))
        return {std::uint64_t(t->seconds)*1000000000ULL+std::uint64_t(t->nanoseconds),id,false};
    // 0x744750 retries MONOTONIC and throws on failure.
    auto t=svc.clock_gettime(1);
    if(!t) throw std::system_error(errno?errno:EIO,std::generic_category(),"clock_gettime(CLOCK_MONOTONIC) failed");
    return {std::uint64_t(t->seconds)*1000000000ULL+std::uint64_t(t->nanoseconds),1,true};
}
std::array<std::uint8_t,32> timestamp_input(Services& svc) {
    std::array<std::uint8_t,32> bytes{};
    const auto time=timestamp(svc).nanoseconds;
    for(unsigned i=0;i<8;++i) bytes[i]=std::uint8_t(time>>(8*i));
    const auto pid=svc.pid();
    for(unsigned i=0;i<4;++i) bytes[8+i]=std::uint8_t(pid>>(8*i));
    svc.system_random(bytes.data()+12,20); // 0x14716c -> 0x19b244
    return bytes;
}
Bytes auto_seeded_generate(Generator& rng,Services& svc,std::size_t n,const Bytes& supplied) {
    if(!supplied.empty()) return rng.generate(n,supplied);
    if(!rng.accepts_input()) return rng.generate(n,{});
    const auto aux=timestamp_input(svc);
    return rng.generate(n,Bytes(aux.begin(),aux.end()));
}
HmacDrbg::HmacDrbg(Services& svc,Hash hash,std::uint64_t interval,bool initialize)
    :services_(svc),hash_(hash),key_(hash==Hash::Sha512?64:32,0),
     value_(key_.size(),1),interval_(interval) {
    if(interval==0) throw std::invalid_argument("reseed interval must be positive");
    if(initialize) (void)generate(1,{}); // AutoSeeded_RNG initialization discards one byte.
}
void HmacDrbg::update(const Bytes& input) {
    // 0x1357ec, HMAC_DRBG_Update: always 0 round, then 1 round if input nonempty.
    for(unsigned round=0;round<(input.empty()?1u:2u);++round) {
        Bytes material=value_;
        material.push_back(static_cast<std::uint8_t>(round));
        material.insert(material.end(),input.begin(),input.end());
        key_=hmac(hash_,key_,material);
        value_=hmac(hash_,key_,value_);
    }
}
void HmacDrbg::reseed_check() {
    const auto pid=services_.pid();
    if(counter_!=0 && (last_pid_==0 || pid==last_pid_) && counter_<interval_) {
        ++counter_; return;
    }
    counter_=0;last_pid_=pid;
    Bytes seed(32); // Both selected hashes have security_level 256 bits.
    services_.system_random(seed.data(),seed.size());
    update(seed);
    std::fill(seed.begin(),seed.end(),0);
    counter_=1;
}
Bytes HmacDrbg::generate_chunk(std::size_t n,const Bytes& input) {
    if(!input.empty()) update(input);
    Bytes out;out.reserve(n);
    while(out.size()<n) {
        value_=hmac(hash_,key_,value_);
        const auto count=std::min(n-out.size(),value_.size());
        out.insert(out.end(),value_.begin(),value_.begin()+count);
    }
    update(input);
    return out;
}
Bytes HmacDrbg::generate(std::size_t n,const Bytes& input) {
    std::lock_guard<std::mutex> lock(mutex_);
    // 0x185168: zero output absorbs input, without clock/pid/reseed checks here.
    if(n==0) {update(input);if(input.size()>=32) counter_=1;return {};}
    Bytes out;out.reserve(n);
    bool first=true;
    while(out.size()<n) {
        reseed_check();
        auto part=generate_chunk(std::min<std::size_t>(65536,n-out.size()),first?input:Bytes{});
        out.insert(out.end(),part.begin(),part.end());
        first=false;
    }
    return out;
}
std::optional<TimeSpec> NativeServices::clock_gettime(int id) {
#ifdef _WIN32
    // Portable host demonstration only; exact Linux IDs are tested via fixtures.
    if(id!=1) return std::nullopt;
    auto n=std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
    return TimeSpec{n/1000000000,n%1000000000};
#else
    timespec t{};
    if(::clock_gettime(id,&t)!=0) return std::nullopt;
    return TimeSpec{t.tv_sec,t.tv_nsec};
#endif
}
std::uint32_t NativeServices::pid() {
#ifdef _WIN32
    return ::GetCurrentProcessId();
#else
    return static_cast<std::uint32_t>(::getpid());
#endif
}
void NativeServices::system_random(std::uint8_t* out,std::size_t n) {
#ifdef _WIN32
    while(n) {
        auto chunk=static_cast<ULONG>(std::min<std::size_t>(n,std::numeric_limits<ULONG>::max()));
        if(::BCryptGenRandom(nullptr,out,chunk,BCRYPT_USE_SYSTEM_PREFERRED_RNG)!=0)
            throw std::runtime_error("BCryptGenRandom failed");
        out+=chunk;n-=chunk;
    }
#else
    if(n) ::arc4random_buf(out,n);
#endif
}
} // namespace prism::clockchain
