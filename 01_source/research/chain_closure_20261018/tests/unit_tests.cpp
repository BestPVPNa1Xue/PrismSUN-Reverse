#include "../src/detection_chains.hpp"
#include <climits>
#include <iostream>
#include <stdexcept>

using namespace prism::chains;
namespace env = prism::environment;
namespace {
int checks = 0;
void check(bool value, const char* name) {
    ++checks;
    if (!value) throw std::runtime_error(name);
}
ReadObservation bytes(std::string s) { return {true, false, std::move(s)}; }
MapEntry map(std::uint64_t start, std::uint64_t end, unsigned p, std::string path) {
    MapEntry m; m.start = start; m.end = end;
    m.permissions = static_cast<std::uint8_t>(p); m.path = std::move(path); return m;
}
void parsing() {
    check(tracer_pid({false,false,{}}) == -2, "tracer open failure");
    check(tracer_pid({true,true,"TracerPid:9"}) == -2, "tracer read failure");
    check(tracer_pid(bytes("")) == -2, "tracer EOF");
    check(tracer_pid(bytes("Name:process\n")) == -1, "tracer missing marker");
    check(tracer_pid(bytes("prefixTracerPid:\t +23x\nTracerPid:99")) == 23, "first nonanchored marker");
    check(tracer_pid(bytes("TracerPid: --5")) == 0, "no digits");
    check(tracer_pid(bytes("TracerPid: \v\f\r\n-9")) == -9, "ASCII whitespace");
    check(tracer_pid(bytes(std::string("Name:\0TracerPid:3",17))) == -1, "status NUL boundary");
    check(tracer_pid(bytes(std::string(2037,'x')+"TracerPid:9")) == 0, "2047 byte read boundary");
    check(tracer_pid(bytes(std::string(2047,'x')+"TracerPid:9")) == -1, "marker outside read");
    check(tracer_pid(bytes("TracerPid:2147483648")) == INT_MIN, "signed overflow wraps");
    check(tracer_pid(bytes("TracerPid:4294967297")) == 1, "positive overflow wraps");
    check(atoi32("-4294967295") == 1, "negative overflow wraps");
    check(!prism_tracer_positive(-2) && !prism_tracer_positive(INT_MIN), "errors and negatives not tracer hits");
    check(prism_tracer_positive(1), "positive tracer hit");
    check(cmdline_first(bytes(std::string("pkg:worker\0other",16))) == "pkg:worker", "cmdline preserves colon");
    check(cmdline_first(bytes(std::string(300,'a'))).size() == 255, "cmdline 255 limit");
    check(cmdline_first({false,false,"pkg"}).empty(), "cmdline failure empty");
    auto s = seccomp_status(bytes("prefixSeccomp:2\nSeccomp_filters:\t3\nNoNewPrivs:1"));
    check(s.mode == 2 && s.filters == 3 && s.no_new_privs && !s.error, "status three fields");
    s = seccomp_status(bytes("Seccomp:1\nNoNewPrivs:2"));
    check(s.mode == 1 && s.filters == -1 && !s.no_new_privs && !s.error, "missing field not variant error");
    check(seccomp_status({false,false,{}}).error == 0xfa1, "status open diagnostic");
    check(seccomp_status(bytes("")).error == 0xfa2, "status EOF diagnostic");
    check(seccomp_status({true,true,"x"}).error == 0xfa2, "status read diagnostic");
    check(seccomp_status(bytes(std::string(4095,'x')+"Seccomp_filters:3")).filters == -1, "4095 limit");
    check(seccomp_status(bytes("Seccomp::: +4x")).mode == 4, "skip extra colons");
}
void maps() {
    const std::string a="1000-2000 r-xp 00000000 08:01 7 /system/lib64/libc.so\n";
    const std::string b="2000-3000 r--p 00001000 08:01 7 /system/lib64/libc.so (deleted)\n";
    const auto all=filter_maps(a+b,"",false);
    check(all.entries.size()==2 && all.entries[1].path.find("(deleted)")!=std::string::npos, "empty needle and deleted inclusion");
    check(filter_maps(a+b,"libc.so",true).entries.size()==1, "deleted exclusion");
    check(filter_maps(a,"r-xp").entries.size()==1, "requested searches whole line");
    check(filter_maps(a,"missing").entries.empty(), "missing requested");
    check(filter_maps(a.substr(0,a.size()-1),"libc.so").entries[0].path=="/system/lib64/libc.s", "unconditional final-byte removal");
    check(filter_maps(a,"libc.so",true,false).entries.empty(), "maps open failure empty");
    check(!filter_maps(a,"",true,true,false).complete, "fdopen failure incomplete");
    auto m=parse_native_maps_line("3000-1000 rwxs 20 ff:ab 8   /path with spaces");
    check(m && m->start==0x3000 && m->end==0x1000, "inverted range accepted");
    check(m && m->permissions==7 && !m->private_mapping && m->file_offset==0x20, "permissions offset fields");
    check(m && m->path=="/path with spaces", "preserve pathname spaces");
    m=parse_native_maps_line("1000-2000 zzzp 0 00:00 0");
    check(m && m->permissions==0 && m->private_mapping && m->path.empty(), "unusual permissions empty path");
    check(!parse_native_maps_line("1000-2000 r-xp 0 bad"), "seven conversions required");
    check(filter_maps("\nmalformed\n"+a,"",false).discarded==2, "bad lines discarded");
    check(all.entries[0].start==0x1000 && all.entries[1].start==0x2000, "maps order");
    check(filter_maps("1000-2000 r-xp 0 00:00 0 /libc.so\r\n","libc.so").entries[0].path=="/libc.so\r", "CR preserved");
    const auto nul=std::string("libc.so\0unmatched",17);
    check(filter_maps(a,nul).entries.size()==1, "needle C boundary");
}
void handlers() {
    MapsObservation m;
    m.entries={map(0x1000,0x2000,0,"/first"),map(0x1000,0x3000,5,"/second")};
    check(!locate_sigsys_handler(true,0,m).active && !locate_sigsys_handler(true,1,m).active,"0/1 inactive");
    check(locate_sigsys_handler(false,0,m).error==0x1389,"query failure");
    check(locate_sigsys_handler(true,0x1000,m).path=="/first","first interval includes start no permission requirement");
    check(locate_sigsys_handler(true,0x2000,m).path=="/second","half-open interval end");
    check(locate_sigsys_handler(true,0x3000,m).path.empty(),"unmapped handler empty path");
    m.complete=false;
    check(!locate_sigsys_handler(true,0x1000,m).complete,"maps failure propagated");
    check(locate_sigsys_handler(true,0,m).complete,"inactive ignores maps failure");
    HandlerInfo h; h.active=false;
    check(handler_reason(h,0,0,"pkg").reason==0,"reason0");
    h.active=true;
    check(handler_reason(h,0,0,"pkg").reason==11,"reason11");
    h.path="/system/lib64/libc.so";
    check(handler_reason(h,99,0,"pkg").reason==2,"reason2");
    h.path="/data/local/tmp/a.so";
    check(handler_reason(h,0,0,"pkg").reason==12,"reason12");
    h.path="/data/app/other-x/base.apk";
    check(handler_reason(h,1,0,"pkg").reason==3,"reason3 does not compare extracted package");
    check(!handler_reason(h,2,0,"pkg").reason,"probe required has no invented verdict");
    check(handler_reason(h,2,0,"pkg",true).reason==10,"reason10");
    check(handler_reason(h,2,0,"pkg",false).reason==4,"reason4");
    check(handler_reason(h,0,0x7fffffffu,"pkg").probe_required,"signed layer bound wraps");
    check(handler_reason(h,0,0xffffffffu,"pkg").reason==3,"layer max wraps to zero");
    h.path="/data/data/pkg:worker/file";
    check(handler_reason(h,0,0,"pkg:worker").reason==3,"process colon prefix retained");
    check(handler_reason(h,0,0,"pkg").reason==12,"no normalization to main package");
    h.path="/data/user/0/pkg/file";
    check(handler_reason(h,0,0,"pkg").reason==3,"user0 recognized prefix");
    h.path="/data/user/10/pkg/file";
    check(handler_reason(h,0,0,"pkg").reason==12,"other user not recognized");
    SeccompStatus s; s.filters=1; h.active=false;
    check(evaluate_seccomp(s,h,0,"").flags.acceptable,"ordinary seccomp accepted");
    s.mode=2; s.no_new_privs=true;
    check(evaluate_seccomp(s,h,0,"").flags.acceptable,"mode/nnp do not drive aggregate");
    h.error=0x1389;
    check(evaluate_seccomp(s,h,0,"").flags.acceptable,"handler query error alone accepted");
    s.error=0xfa1;
    check(evaluate_seccomp(s,h,0,"").diagnostic==5006,"status error diagnostic consumer");
    s.error=0; s.filters=2; h.error=0; h.active=true; h.path="/data/app/pkg-x/base.apk";
    const auto unfinished=evaluate_seccomp(s,h,0,"pkg");
    check(!unfinished.complete && unfinished.probe_required && !unfinished.flags.acceptable,"unrun probe incomplete");
    const auto yes=evaluate_seccomp(s,h,0,"pkg",true);
    check(yes.complete && yes.flags.suspicious_handler && yes.flags.excessive_count && yes.handler_source==h.path,"independent flags and source");
    const auto no=evaluate_seccomp(s,h,0,"pkg",false);
    check(no.complete && !no.flags.suspicious_handler && !no.flags.acceptable,"negative probe does not erase count flag");
    check(package_from_install_path("/data/app/pkg-x/base.apk")=="pkg","old install path");
    check(package_from_install_path("/data/app/~~random/pkg-x/base.apk")=="pkg","new install path");
    check(package_from_install_path("/data/app/pkg/dir-x/base.apk")=="pkg/dir","find dash is not slash-bounded");
    check(package_from_install_path("/data/app/~~random").empty(),"missing post-tilde slash");
    check(package_from_install_path("/data/app/-x/base.apk").empty(),"empty package");
    m.complete=true;
    m.entries={map(1,2,0,"/system/base.apk"),map(3,4,0,"/data/app/other-x/base.apk"),map(5,6,0,"/data/app/pkg-x/base.apk")};
    check(select_probe_path(m,"pkg")==m.entries[2].path,"probe package matching");
    check(select_probe_path(m,"")==m.entries[1].path,"empty cmdline first data-app");
    check(select_probe_path(m,"pkg:worker")=="/dev/null","no matched subprocess fallback");
}
struct FakeProbe : ProbeBackend {
    std::vector<std::string> calls;
    bool install=true, trapped=true, restore=true;
    int fd=7;
    std::uint32_t value=0;
    void reset_marker(std::uint32_t v) noexcept override {calls.push_back("reset");value=v;}
    bool install_sigsys() noexcept override {calls.push_back("install");return install;}
    int open_readonly(const char* p) noexcept override {calls.push_back(p);if(trapped)value=kProbeTrapped;return fd;}
    std::uint32_t marker() noexcept override {calls.push_back("marker");return value;}
    void close_fd(int) noexcept override {calls.push_back("close");}
    bool restore_sigsys() noexcept override {calls.push_back("restore");return restore;}
};
void probe() {
    auto effect=sigsys_handler_effect(kProbeInitial,{true,1,56,true});
    check(effect.marker==kProbeTrapped && effect.x0==~std::uint64_t{0},"matching trap changes marker and x0");
    effect=sigsys_handler_effect(kProbeInitial,{true,2,56,true});
    check(effect.marker==kProbeInitial && effect.x0.has_value(),"nonmatching trap still writes x0");
    effect=sigsys_handler_effect(kProbeInitial,{false,1,56,true});
    check(effect.marker==kProbeInitial && effect.x0.has_value(),"null siginfo still writes x0");
    effect=sigsys_handler_effect(kProbeInitial,{true,1,56,false});
    check(effect.marker==kProbeTrapped && !effect.x0,"null context allowed");
    FakeProbe b; auto r=run_probe("/dev/null",b);
    check(r.completed && r.changed && r.restore_succeeded,"probe return");
    check(b.calls==std::vector<std::string>{"reset","install","/dev/null","marker","close","restore"},"probe ordered operations");
    b.calls.clear();b.install=false;r=run_probe("p",b);
    check(r.completed && !r.installed && !r.changed && b.calls.size()==2,"install fail false without open");
    b.calls.clear();b.install=true;b.fd=-1;b.restore=false;r=run_probe("p",b);
    check(r.changed && r.restore_attempted && !r.restore_succeeded,"restore failure does not erase changed result");
    check(b.calls==std::vector<std::string>{"reset","install","p","marker","restore"},"negative fd not closed");
    b.calls.clear();b.trapped=false;r=run_probe("p",b);
    check(!r.changed,"open failure alone not trap");
}
void integrity_and_loop() {
    env::ElfBaseline base; base.initialized=true;
    const std::vector<std::uint8_t> data{1,2,3,4};
    base.sections.push_back({1,0x20,4,4,env::crc32_bswap(data)});
    const env::MemoryReader reader=[&](std::uint64_t a,std::size_t n)->std::optional<std::vector<std::uint8_t>> {
        if(a==0x1020 && n==4) return data;
        return {};
    };
    const std::string maps="1000-2000 r-xp 0 00:00 1 /system/lib64/libc.so\n";
    auto r=compare_library(base,maps,env::Library::Libc,reader);
    check(r.code==env::IntegrityCode::Normal && r.sections_compared==1,"maps-integrity composition");
    r=compare_library(base,maps,env::Library::LibArt,reader);
    check(r.code==env::IntegrityCode::MapsUnavailable,"filtered empty returns57");
    r=compare_library(base,maps,env::Library::Libc,reader,true,false);
    check(!r.complete && !r.code,"fdopen incomplete not57");
    r=compare_library(base,"1000-2000 ---p 0 00:00 1 /libc.so\n",env::Library::Libc,reader);
    check(r.code==env::IntegrityCode::Normal,"nonempty no readable executable can return46");
    const std::string paths="1000-2000 ---p 0 00:00 1 /a/libc.so\n2000-3000 ---p 0 00:00 2 /b/libc.so\n";
    r=compare_library(base,paths,env::Library::Libc,reader);
    check(r.code==env::IntegrityCode::Mismatch && r.local_termination,"path change before permission test");
    base.initialized=false;
    check(compare_library(base,"",env::Library::Libc,reader,true,false).code==env::IntegrityCode::Uninitialized,"uninitialized before maps acquisition");
    env::EnvironmentState state;
    env::EnvironmentCycleInput input; input.library_codes={46,46,46,46};input.tracer_pid=-2;
    auto c=env::run_environment_cycle(state,input);
    check(c.complete && c.ran_integrity && !c.local_termination,"initial full batch and tracer error");
    input.library_codes={};input.tracer_pid=1;
    c=env::run_environment_cycle(state,input);
    check(!c.ran_integrity && c.tracer_positive && c.local_termination,"tracer checked between batches");
    Event20State e; e.baseline16=3;
    const std::vector<MapEntry> entries={map(0,0x5000,4,""),map(0,0x5001,4,""),map(0,0x6000,4,"[anon:jit]"),map(0,0x6000,4,"/dev/zero (deleted)"),map(0,0x6000,1,"")};
    auto count=event20_counts(e,entries,true);
    check(count.delta==-1 && count.empty==1,"event20 strict threshold and wrapped baseline subtraction");
    count=event20_counts(e,{},false,{"injected diagnostic"});
    check(count.delta==0 && count.empty==1 && count.diagnostics.size()==1,"event20 failure preserves prior empty count");
}
JsonValue text(const char* value) {return {16,0,std::string(value),{}};}
struct FakeClasses : ClassBackend {
    bool available=true, pending=false;
    int acquired=0,released=0,deleted=0,cleared=0;
    std::vector<std::string> queried;
    bool acquire() noexcept override {++acquired;return available;}
    void release() noexcept override {++released;}
    std::uintptr_t find_class(const char* name) noexcept override {
        queried.emplace_back(name);pending=queried.back()=="bad";return queried.back()=="missing"?0:7;
    }
    bool exception_pending() noexcept override {return pending;}
    void clear_exception() noexcept override {pending=false;++cleared;}
    void delete_local_ref(std::uintptr_t) noexcept override {++deleted;}
};
void classes() {
    FakeClasses b;auto r=probe_classes(nullptr,b);
    check(r.event==22 && b.acquired==0,"null config empty event without JNI");
    JsonValue a{32,0,{}, {}};
    check(probe_classes(&a,b).event==22 && b.acquired==0,"empty array skips JNI");
    JsonValue nonarray=text("x");
    check(probe_classes(&nonarray,b).event==22 && b.acquired==0,"invalid config empty event");
    a.children={text("one"),text("bad"),text("missing"),text("one"),JsonValue{8,4,{},{}},text("ignored")};
    r=probe_classes(&a,b);
    check(r.event==22 && r.visible==std::vector<std::string>{"one","one"},"visible order and duplicates");
    check(r.stopped_at_non_string && b.queried.size()==4,"non-string stops remaining list");
    check(r.cleared==1 && r.deleted==2 && b.cleared==1 && b.deleted==2,"exception branch skips deletion even nonnull mock ref");
    check(b.released==1,"scope releases after success");
    b.available=false;r=probe_classes(&a,b);
    check(!r.event && r.diagnostic==0xbba && b.released==2,"JNI error no event releases scope");
    b.available=true;a.children={{16,0,std::string("one\0suffix",10),{}}};
    r=probe_classes(&a,b);
    check(r.visible==std::vector<std::string>{"one"} && b.queried.back()=="one","C string NUL boundary");
    a.children={{16,0,{}, {}}};r=probe_classes(&a,b);
    check(!r.complete && !r.event,"null valuestring incomplete");
    a.type=32|256;a.children={text("slash/Class"),text("dot.Class")};
    r=probe_classes(&a,b);
    check(r.visible==std::vector<std::string>{"slash/Class","dot.Class"},"low byte type and no class-name normalization");
    JsonValue root{32,0,{},{{8,291,{},{}},a,text("extra")}};
    auto request=request_view(root);
    check(request && request->task_id==35 && request->config==&root.children[1],"task low byte and borrowed second item");
    root.children[0].type=16;check(!request_view(root),"request first item must number");
    root.children[0].type=8;root.children[1].type=16;check(!request_view(root),"request second item must array");
    root.children.resize(1);check(!request_view(root),"request requires two items");
}
} // namespace
int main() {
    try {
        parsing(); maps(); handlers(); probe(); integrity_and_loop(); classes();
        std::cout<<"{\"suite\":\"chain-boundaries\",\"checks\":"<<checks<<",\"passed\":true,\"runtime\":\"host synthetic inputs; original sample not executed\"}\n";
    } catch(const std::exception& e) { std::cerr<<"FAIL after "<<checks<<": "<<e.what()<<'\n';return 1; }
}
