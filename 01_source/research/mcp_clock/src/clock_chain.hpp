#pragma once
#include <array>
#include <cstdint>
#include <mutex>
#include <optional>
#include <string>
#include <vector>

namespace prism::clockchain {
using Bytes=std::vector<std::uint8_t>;
struct TimeSpec { std::int64_t seconds, nanoseconds; };
class Services {
public:
    virtual ~Services()=default;
    virtual std::optional<TimeSpec> clock_gettime(int id)=0;
    virtual std::uint32_t pid()=0;
    virtual void system_random(std::uint8_t*,std::size_t)=0;
};
class NativeServices final : public Services {
public:
    std::optional<TimeSpec> clock_gettime(int) override;
    std::uint32_t pid() override;
    void system_random(std::uint8_t*,std::size_t) override;
};
struct ClockValue { std::uint64_t nanoseconds; int selected_id; bool fallback; };
ClockValue timestamp(Services&);
std::array<std::uint8_t,32> timestamp_input(Services&);
class Generator {
public:
    virtual ~Generator()=default;
    virtual bool accepts_input() const=0;
    virtual Bytes generate(std::size_t,const Bytes& input)=0;
};
// 0xf4f9c -> 0xf5198, or direct 0xf5734 for supplied nonempty input.
Bytes auto_seeded_generate(Generator&,Services&,std::size_t,const Bytes& supplied={});
enum class Hash { Sha512, Sha256 };
Bytes digest(Hash,const Bytes&);
Bytes hmac(Hash,const Bytes& key,const Bytes& message);
std::string hex(const Bytes&);
Bytes unhex(const std::string&);

// Concrete consumer recovered from vtable 0x78fa50 (Botan::HMAC_DRBG).
// Services supplies the original System_RNG role; optional Entropy_Sources is
// null in the recovered AutoSeeded_RNG constructor.
class HmacDrbg final : public Generator {
public:
    HmacDrbg(Services&,Hash=Hash::Sha512,std::uint64_t reseed_interval=1024,
             bool initialize=true);
    bool accepts_input() const override {return true;}
    Bytes generate(std::size_t,const Bytes&) override;
    std::uint64_t reseed_counter() const {return counter_;}
private:
    Services& services_;
    Hash hash_;
    Bytes key_,value_;
    std::uint64_t counter_=0,interval_;
    std::uint32_t last_pid_=0;
    std::mutex mutex_;
    void update(const Bytes&);
    void reseed_check();
    Bytes generate_chunk(std::size_t,const Bytes&);
};
} // namespace prism::clockchain
