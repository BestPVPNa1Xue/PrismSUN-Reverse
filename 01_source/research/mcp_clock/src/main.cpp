#include "mcp_chain.hpp"
#include "clock_chain.hpp"
#include <iostream>
#include <stdexcept>

using namespace prism::clockchain;
struct FixtureServices final : Services {
    Bytes seed;
    explicit FixtureServices(Bytes s):seed(std::move(s)){}
    std::optional<TimeSpec> clock_gettime(int) override {return TimeSpec{1,2};}
    std::uint32_t pid() override{return 1234;}
    void system_random(std::uint8_t* out,std::size_t n) override {
        if(seed.size()!=n) throw std::runtime_error("fixture seed size mismatch");
        std::copy(seed.begin(),seed.end(),out);
    }
};
int main(int argc,char** argv) try {
    NativeServices svc;
    const std::string command=argc>1?argv[1]:"help";
    if(command=="mcp") {
        prism::mcp::NativeFiles fs;
        const auto scan=prism::mcp::collect(fs,svc.pid());
        auto payload=prism::mcp::event32_payload(scan);
        if(!payload) throw std::runtime_error("indeterminate original parser stack bytes");
        std::cout<<"{\"event\":32,\"payload\":"<<*payload<<"}\n";
    } else if(command=="clock") {
        const auto t=timestamp(svc);
        HmacDrbg rng(svc);
        const auto bytes=auto_seeded_generate(rng,svc,32);
        std::cout<<"{\"clock_id\":"<<t.selected_id<<",\"nanoseconds\":"<<t.nanoseconds
                 <<",\"rng\":\"HMAC_DRBG(SHA-512)\",\"random\":\""<<hex(bytes)<<"\"}\n";
    } else if((command=="hash512"||command=="hash256")&&argc==3) {
        std::cout<<hex(digest(command=="hash512"?Hash::Sha512:Hash::Sha256,unhex(argv[2])))<<'\n';
    } else if((command=="hmac512"||command=="hmac256")&&argc==4) {
        std::cout<<hex(hmac(command=="hmac512"?Hash::Sha512:Hash::Sha256,unhex(argv[2]),unhex(argv[3])))<<'\n';
    } else if(command=="drbg"&&argc==6) {
        FixtureServices f(unhex(argv[3]));
        const auto hash=std::string(argv[2])=="512"?Hash::Sha512:Hash::Sha256;
        HmacDrbg rng(f,hash,1024,false);
        std::cout<<hex(rng.generate(std::stoull(argv[5]),unhex(argv[4])))<<'\n';
    } else {
        std::cout<<"Usage: prism_mcp_clock mcp | clock | hash512 HEX | hash256 HEX\n"
                 <<"       prism_mcp_clock hmac512 KEYHEX MSGHEX | hmac256 KEYHEX MSGHEX\n"
                 <<"       prism_mcp_clock drbg 512|256 SEEDHEX INPUTHEX LENGTH\n";
        return command=="help"?0:2;
    }
    return 0;
} catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 1;}
