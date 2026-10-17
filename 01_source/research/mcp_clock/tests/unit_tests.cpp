#include "mcp_chain.hpp"
#include "clock_chain.hpp"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <stdexcept>
#include <system_error>

namespace mc=prism::mcp;
namespace cc=prism::clockchain;
unsigned checks=0;
void check(bool b,const char* message){++checks;if(!b)throw std::runtime_error(message);}
struct Files final : mc::FileOps {
    std::vector<mc::Entry> first,second;
    std::map<std::string,std::string> links;
    std::map<std::string,cc::Bytes> files;
    cc::Bytes current;
    std::size_t cursor=0;
    int passes=0,closes=0,opens=0;
    bool first_ok=true,second_ok=true,seek_ok=true;
    std::vector<std::string> directories;
    bool enumerate(const std::string& path,const std::function<bool(const mc::Entry&)>& f) override {
        directories.push_back(path);
        const bool one=passes++==0;
        if(!(one?first_ok:second_ok))return false;
        for(const auto& e:one?first:second) if(!f(e))break;
        return true;
    }
    std::optional<std::string> readlink(const std::string& p) override {
        auto it=links.find(p);return it==links.end()?std::nullopt:std::optional<std::string>{it->second};
    }
    int open_read(const std::string& p) override {
        ++opens;auto it=files.find(p);if(it==files.end())return -1;
        current=it->second;cursor=0;return 42;
    }
    std::int64_t read(int,void* p,std::size_t n) override {
        const auto got=std::min(n,cursor<current.size()?current.size()-cursor:0);
        if(got)std::memcpy(p,current.data()+cursor,got);
        cursor+=got;return static_cast<std::int64_t>(got);
    }
    std::int64_t seek(int,std::int64_t n) override {if(!seek_ok)return -1;cursor=static_cast<std::size_t>(n);return n;}
    void close(int) override{++closes;}
};
cc::Bytes file_bytes(std::string text,bool nul=true) {
    cc::Bytes b(24,0);b[0]='M';b[1]='C';b[2]='P';b[3]='K';
    b.insert(b.end(),text.begin(),text.end());if(nul)b.push_back(0);return b;
}
struct Services final : cc::Services {
    std::vector<int> calls;
    std::vector<std::optional<cc::TimeSpec>> answers;
    std::size_t at=0;
    unsigned pid_calls=0,random_calls=0;
    std::uint32_t process=0x12345678;
    bool fail_random=false;
    std::optional<cc::TimeSpec> clock_gettime(int id) override {
        calls.push_back(id);return at<answers.size()?answers[at++]:std::nullopt;
    }
    std::uint32_t pid() override{++pid_calls;return process;}
    void system_random(std::uint8_t* p,std::size_t n) override {
        ++random_calls;if(fail_random)throw std::runtime_error("entropy failure");
        for(std::size_t i=0;i<n;++i)p[i]=static_cast<std::uint8_t>(i);
    }
};
struct Sink final : cc::Generator {
    bool accepts=true;unsigned calls=0;cc::Bytes last;
    bool accepts_input() const override{return accepts;}
    cc::Bytes generate(std::size_t n,const cc::Bytes& in) override {++calls;last=in;return cc::Bytes(n,0xaa);}
};
int main() try {
    check(mc::ends_with("a.mcp",".mcp"),"suffix");
    check(!mc::ends_with("a.mcp (deleted)",".mcp"),"deleted suffix");
    check(!mc::ends_with("a.MCP",".mcp"),"case sensitivity");
    check(!mc::ends_with("cp",".mcp"),"short suffix");
    check(mc::starts_with("x",""),"empty prefix");
    check(mc::starts_with("/abcd/f.mcp","/abc"),"byte prefix not directory boundary");
    check(!mc::starts_with("x/abc","/abc"),"prefix not contains");
    Files f;
    auto parsed=mc::parse_file(f,"missing");
    check(parsed.status==mc::ParseStatus::OpenFailed&&parsed.text.empty()&&f.closes==0,"open failure");
    f.files["a"]=file_bytes("Name");parsed=mc::parse_file(f,"a");
    check(parsed.text=="Name"&&parsed.complete()&&f.closes==1,"MCPK parser");
    f.files["a"][0]='Z';parsed=mc::parse_file(f,"a");
    check(parsed.status==mc::ParseStatus::WrongMagic&&parsed.text.empty(),"bad magic");
    f.files["a"]={'M','C'};parsed=mc::parse_file(f,"a");
    check(!parsed.complete(),"short header undefined stack");
    f.files["a"]={'Z'};parsed=mc::parse_file(f,"a");
    check(parsed.status==mc::ParseStatus::WrongMagic,"known mismatch before missing byte");
    f.files["a"]=file_bytes("",false);parsed=mc::parse_file(f,"a");
    check(!parsed.complete(),"empty first read undefined stack");
    f.files["a"]=file_bytes("",true);parsed=mc::parse_file(f,"a");
    check(parsed.complete()&&parsed.text.empty(),"zero terminator");
    f.files["a"]=file_bytes(std::string(80,'Q'));parsed=mc::parse_file(f,"a");
    check(parsed.text==std::string(64,'Q'),"64 byte bound");
    f.files["a"]=file_bytes("XY",false);parsed=mc::parse_file(f,"a");
    check(parsed.text=="X"+std::string(63,'Y')&&parsed.ignored_io_failure,"EOF stale byte behavior");
    f.files["a"]=file_bytes("later");f.seek_ok=false;parsed=mc::parse_file(f,"a");
    check(parsed.text.empty()&&parsed.ignored_io_failure,"ignored failed seek preserves cursor");
    Files scan;
    scan.first={{"0",8},{"1",10},{"2",10}};
    scan.second={{"3",10},{"4",10},{"5",10},{"6",10},{"7",8},{"8",0},{"9",10}};
    const std::string dir="/proc/77/fd/";
    scan.links[dir+"1"]="/abc/PrismSUNScripts.mcp";
    scan.links[dir+"2"]="/other/PrismSUNScripts.mcp";
    scan.links[dir+"3"]="/abc/a.mcp";scan.links[dir+"4"]="/abcd/b.mcp";
    scan.links[dir+"5"]="/else/a.mcp";scan.links[dir+"6"]="/abc/a.mcp";
    scan.links[dir+"7"]="/abc/regular.mcp";scan.links[dir+"8"]="/abc/unknown.mcp";
    scan.links[dir+"9"]="/abc/a.mcp (deleted)";
    scan.files["/abc/a.mcp"]=file_bytes("One");
    auto s=mc::collect(scan,77);
    check(s.directory=="/proc/77/fd"&&scan.directories.size()==2,"two pid fd passes");
    check(s.prefix=="/ab"&&s.marker_found,"pos minus one first marker");
    check(s.values==std::vector<std::string>{"a.mcp:One","b.mcp:","a.mcp:One"},"order duplicates errors and prefix");
    check(mc::event32_payload(s)=="[\"a.mcp:One\",\"b.mcp:\",\"a.mcp:One\"]","event array");
    Files no_marker;no_marker.first_ok=false;no_marker.second={{"1",10}};
    no_marker.links[dir+"1"]="naked.mcp";
    s=mc::collect(no_marker,77);
    check(s.values==std::vector<std::string>{"naked.mcp:"}&&!s.marker_found,"missing prefix means accept all");
    Files empty;s=mc::collect(empty,77);check(mc::event32_payload(s)=="[]","always empty event");
    Files unknown;unknown.second={{"1",10}};unknown.links[dir+"1"]="a.mcp";
    unknown.files["a.mcp"]={'M'};s=mc::collect(unknown,77);
    check(!s.complete()&&!mc::event32_payload(s),"indeterminate scan has no fabricated event");
    Files zero;zero.first={{"1",10}};zero.links[dir+"1"]="/PrismSUNScripts.mcp";
    check(mc::collect(zero,77).prefix=="/PrismSUNScripts.mcp","pos zero unsigned wrap");
    check(mc::json_string("a\n\"\\")=="\"a\\n\\\"\\\\\"","JSON escaping");
    for(unsigned success=0;success<5;++success) {
        Services svc;svc.answers.resize(success);svc.answers.push_back(cc::TimeSpec{2,3});
        auto t=cc::timestamp(svc);std::vector<int> ids{4,1,2,3,1};ids.resize(success+1);
        check(svc.calls==ids&&t.nanoseconds==2000000003ULL&&t.fallback==(success==4),"clock priority and retry");
    }
    Services failed;bool threw=false;try{cc::timestamp(failed);}catch(const std::system_error&){threw=true;}
    check(threw&&failed.calls==std::vector<int>{4,1,2,3,1},"all clocks fail throws");
    Services svc;svc.answers={cc::TimeSpec{1,2}};auto aux=cc::timestamp_input(svc);
    check(cc::hex(cc::Bytes(aux.begin(),aux.end()))=="02ca9a3b0000000078563412000102030405060708090a0b0c0d0e0f10111213","LE time pid and 20 bytes");
    Services wrap;wrap.answers={cc::TimeSpec{-1,0}};
    check(cc::timestamp(wrap).nanoseconds==std::uint64_t(-1000000000LL),"ARM64 wrap semantics");
    Sink sink;Services direct;auto out=cc::auto_seeded_generate(sink,direct,3,{1,2});
    check(out.size()==3&&sink.last==cc::Bytes{1,2}&&direct.calls.empty()&&direct.random_calls==0,"supplied input bypasses clocks");
    sink.accepts=false;cc::auto_seeded_generate(sink,direct,0);
    check(sink.last.empty()&&direct.pid_calls==0,"non-input RNG bypasses auxiliary data");
    sink.accepts=true;Services zero_out;zero_out.answers={cc::TimeSpec{0,1}};
    cc::auto_seeded_generate(sink,zero_out,0);
    check(sink.last.size()==32&&zero_out.random_calls==1,"zero output still supplies timestamps");
    Services state;cc::HmacDrbg rng(state,cc::Hash::Sha512,2,false);
    rng.generate(1,{});check(state.random_calls==1&&rng.reseed_counter()==1,"initial reseed");
    rng.generate(1,{});check(state.random_calls==1&&rng.reseed_counter()==2,"counter advance");
    rng.generate(1,{});check(state.random_calls==2&&rng.reseed_counter()==1,"interval reseed");
    ++state.process;rng.generate(1,{});check(state.random_calls==3,"fork pid reseed");
    auto calls=state.pid_calls;rng.generate(0,cc::Bytes(32,9));
    check(state.pid_calls==calls&&rng.reseed_counter()==1,"zero output absorbs and marks seeded");
    Services init;cc::HmacDrbg initialized(init);check(init.random_calls==1&&initialized.reseed_counter()==1,"constructor discards one output byte");
    Services entropy_failure;entropy_failure.fail_random=true;cc::HmacDrbg bad(entropy_failure,cc::Hash::Sha512,1024,false);
    threw=false;try{bad.generate(1,{});}catch(const std::runtime_error&){threw=true;}
    check(threw&&bad.reseed_counter()==0,"entropy failure propagates");
    check(cc::hex(cc::digest(cc::Hash::Sha256,{}))=="e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855","SHA256 empty");
    check(cc::hex(cc::digest(cc::Hash::Sha512,{}))=="cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e","SHA512 empty");
    std::cout<<"PASS "<<checks<<" checks\n";return 0;
} catch(const std::exception& e) {std::cerr<<"FAIL after "<<checks<<": "<<e.what()<<'\n';return 1;}
