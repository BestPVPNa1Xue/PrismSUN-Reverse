#include "clock_chain.hpp"
#include <algorithm>
#include <array>
#include <stdexcept>

namespace prism::clockchain {
namespace {
#include "sha_constants.inc"
template<class T> T rotr(T x,unsigned n) {return (x>>n)|(x<<(sizeof(T)*8-n));}
template<class T> Bytes sha2(const Bytes& input,const T* iv,const T* constants,unsigned rounds) {
    constexpr bool wide=sizeof(T)==8;
    constexpr std::size_t block=sizeof(T)*16, length_bytes=wide?16:8;
    Bytes padded=input;
    padded.push_back(0x80);
    while((padded.size()+length_bytes)%block) padded.push_back(0);
    const auto size=static_cast<std::uint64_t>(input.size());
    if constexpr(wide) {
        const auto upper=size>>61;
        for(int i=7;i>=0;--i) padded.push_back(std::uint8_t(upper>>(i*8)));
    }
    for(int i=7;i>=0;--i) padded.push_back(std::uint8_t((size*8)>>(i*8)));
    std::array<T,8> state{};
    std::copy_n(iv,8,state.begin());
    for(std::size_t off=0;off<padded.size();off+=block) {
        std::array<T,80> w{};
        for(unsigned i=0;i<16;++i)
            for(unsigned j=0;j<sizeof(T);++j) w[i]=(w[i]<<8)|padded[off+i*sizeof(T)+j];
        for(unsigned i=16;i<rounds;++i) {
            const T a=w[i-15],b=w[i-2];
            const T s0=wide?(rotr(a,1)^rotr(a,8)^(a>>7)):(rotr(a,7)^rotr(a,18)^(a>>3));
            const T s1=wide?(rotr(b,19)^rotr(b,61)^(b>>6)):(rotr(b,17)^rotr(b,19)^(b>>10));
            w[i]=w[i-16]+s0+w[i-7]+s1;
        }
        T a=state[0],b=state[1],c=state[2],d=state[3],e=state[4],f=state[5],g=state[6],h=state[7];
        for(unsigned i=0;i<rounds;++i) {
            const T s1=wide?(rotr(e,14)^rotr(e,18)^rotr(e,41)):(rotr(e,6)^rotr(e,11)^rotr(e,25));
            const T s0=wide?(rotr(a,28)^rotr(a,34)^rotr(a,39)):(rotr(a,2)^rotr(a,13)^rotr(a,22));
            const T t1=h+s1+((e&f)^(~e&g))+constants[i]+w[i];
            const T t2=s0+((a&b)^(a&c)^(b&c));
            h=g;g=f;f=e;e=d+t1;d=c;c=b;b=a;a=t1+t2;
        }
        state[0]+=a;state[1]+=b;state[2]+=c;state[3]+=d;
        state[4]+=e;state[5]+=f;state[6]+=g;state[7]+=h;
    }
    Bytes out;
    for(auto word:state) for(int i=static_cast<int>(sizeof(T))-1;i>=0;--i) out.push_back(std::uint8_t(word>>(i*8)));
    return out;
}
}
Bytes digest(Hash hash,const Bytes& input) {
    if(hash==Hash::Sha512) return sha2(input,iv512,k512,80);
    return sha2(input,iv256,k256,64);
}
Bytes hmac(Hash hash,const Bytes& key,const Bytes& message) {
    const std::size_t block=hash==Hash::Sha512?128:64;
    Bytes normalized=key.size()>block?digest(hash,key):key;
    normalized.resize(block,0);
    Bytes inner(block),outer(block);
    for(std::size_t i=0;i<block;++i) {inner[i]=normalized[i]^0x36;outer[i]=normalized[i]^0x5c;}
    inner.insert(inner.end(),message.begin(),message.end());
    auto mid=digest(hash,inner);
    outer.insert(outer.end(),mid.begin(),mid.end());
    return digest(hash,outer);
}
std::string hex(const Bytes& bytes) {
    constexpr char h[]="0123456789abcdef";
    std::string out;out.reserve(bytes.size()*2);
    for(auto b:bytes) {out+=h[b>>4];out+=h[b&15];}return out;
}
Bytes unhex(const std::string& s) {
    if(s.size()%2) throw std::invalid_argument("odd hex length");
    auto digit=[](char c)->unsigned {if(c>='0'&&c<='9') return c-'0';if(c>='a'&&c<='f') return c-'a'+10;
        if(c>='A'&&c<='F') return c-'A'+10;
        throw std::invalid_argument("invalid hex");};
    Bytes out;
    for(std::size_t i=0;i<s.size();i+=2) out.push_back(std::uint8_t(digit(s[i])*16+digit(s[i+1])));
    return out;
}
}
