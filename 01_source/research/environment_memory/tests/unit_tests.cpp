#include "environment_memory.hpp"
#include "observed_models.h"
#include "class_probe_model.h"
#include <iostream>
#include <stdexcept>
#include <limits>

using namespace prism::environment;
static unsigned checks = 0;
static void check(bool value, const char* name) {
    if (!value) throw std::runtime_error(name);
    ++checks;
}
static void put(std::vector<std::uint8_t>& b, std::size_t at, std::uint64_t n, unsigned width) {
    for (unsigned i=0;i<width;++i) b.at(at+i)=static_cast<std::uint8_t>(n>>(8*i));
}
static std::vector<std::uint8_t> elf() {
    std::vector<std::uint8_t> b(512);
    b[0]=0x7f;b[1]='E';b[2]='L';b[3]='F';b[4]=2;b[5]=1;
    put(b,18,183,2);put(b,40,64,8);put(b,58,64,2);put(b,60,3,2);
    for(unsigned i=0;i<3;++i) {
        put(b,64+64*i+8,6,8);put(b,64+64*i+24,300+4*i,8);put(b,64+64*i+32,4,8);
        b[300+4*i]=static_cast<std::uint8_t>(i+1);
    }
    return b;
}
static void baseline_tests() {
    auto b=elf();auto base=make_elf_baseline(b,0x12345678);
    check(base && base->initialized && base->sections.size()==2,"first two exec sections");
    check(base->sections[0].file_offset==300 && base->sections[1].file_offset==304,"section offsets");
    check((base->sections[0].digest_xor_mask ^ base->mask)==crc32_bswap(b.data()+300,4),"mask reversibility");
    check(make_elf_baseline(b,0,10)->sections.size()==2,"native maximum remains two");
    auto bad=b;bad.resize(63);check(!make_elf_baseline(bad),"short ELF");
    bad=b;bad[0]=0;check(!make_elf_baseline(bad),"bad magic");
    bad=b;bad[5]=2;check(!make_elf_baseline(bad),"big endian rejected");
    bad=b;bad[18]=0;check(!make_elf_baseline(bad),"wrong machine");
    bad=b;put(bad,40,500,8);check(!make_elf_baseline(bad),"truncated section table");
    bad=b;put(bad,64+24,510,8);check(!make_elf_baseline(bad),"section data overrun");
    bad=b;for(unsigned i=0;i<3;++i)put(bad,64+64*i+8,0,8);
    check(!make_elf_baseline(bad)->initialized,"no executable sections stays uninitialized");
    check(!make_elf_baseline(ByteView{nullptr,512}),"null view");
}
static void mapping_tests() {
    auto line=parse_maps_line("1000-2000 r-xp 00001000 08:01 17       /system/lib64/libc.so");
    check(line && line->start==0x1000 && line->file_offset==0x1000 && line->permissions==5 && line->private_mapping,"maps fields");
    check(line->path=="/system/lib64/libc.so","maps path whitespace");
    check(parse_maps_line("1000-2000 rw-s 0 00:00 0")->path.empty(),"anonymous mapping");
    check(!parse_maps_line("2000-1000 r-xp 0 00:00 0"),"reversed range");
    check(!parse_maps_line("1000-2000 rzxp 0 00:00 0"),"bad permissions");
    check(parse_maps_text("junk\n1000-2000 r--p 0 00:00 0 /a\n").size()==1,"skip malformed line");
    const std::vector<std::uint8_t> data{1,2,3,4};
    ElfBaseline base; base.initialized=true;base.mask=0xdeadbeef;
    base.sections={{0,0x20,4,6,crc32_bswap(data)^base.mask},{1,0x120,4,6,crc32_bswap(data)^base.mask}};
    std::vector<std::uint64_t> reads;
    auto reader=[&](std::uint64_t a,std::size_t)->std::optional<std::vector<std::uint8_t>> {reads.push_back(a);return data;};
    auto fresh=base;fresh.initialized=false;
    check(compare_mappings(fresh,{},reader).code==IntegrityCode::Uninitialized,"baseline precedes empty maps");
    check(compare_mappings(base,{},reader).code==IntegrityCode::MapsUnavailable,"empty candidates 57");
    MapEntry r{0x1000,0x1100,0,1,true,"/a"}, rx{0x2000,0x2100,0x1000,5,true,"/a"};
    auto got=compare_mappings(base,{r,rx},reader);
    check(got.complete && got.code==IntegrityCode::Normal && got.selected_base==0x1000,"fallback selected once for all sections");
    check(reads==std::vector<std::uint64_t>{0x1020,0x1120} && base.fallback_base==0,"fallback consumed for whole batch");
    reads.clear();got=compare_mappings(base,{rx},reader);
    check(reads==std::vector<std::uint64_t>{0x2020,0x2120},"no fallback still attempts original address beyond map");
    reads.clear();got=compare_mappings(base,{rx,MapEntry{0x3000,0x4000,0,5,true,"/different"}},reader);
    check(got.code==IntegrityCode::Normal && got.mappings_seen==1,"return after first executable candidate");
    auto other=rx;other.path="/b";reads.clear();got=compare_mappings(base,{r,other},reader);
    check(got.local_termination && got.code==IntegrityCode::Mismatch && reads.empty(),"path mismatch precedes hashing");
    other.permissions=0;got=compare_mappings(base,{r,other},reader);
    check(got.local_termination,"path mismatch precedes readability");
    got=compare_mappings(base,{r},reader);
    check(got.code==IntegrityCode::Normal && got.sections_compared==0 && base.fallback_base==r.start,"no executable candidate returns 46 and retains fallback");
    reads.clear();got=compare_mappings(base,{rx},reader);
    check(got.selected_base==r.start && base.fallback_base==0,"fallback persists across calls");
    auto mutate=[&](std::uint64_t,std::size_t)->std::optional<std::vector<std::uint8_t>> {return std::vector<std::uint8_t>{1,2,3,5};};
    got=compare_mappings(base,{rx},mutate);
    check(got.code==IntegrityCode::Mismatch && got.sections_compared==1 && got.stopped_on_mismatch && !got.local_termination,"digest mismatch returns 12 without comparator termination");
    auto failed=[](std::uint64_t,std::size_t)->std::optional<std::vector<std::uint8_t>> {return std::nullopt;};
    got=compare_mappings(base,{rx},failed);
    check(!got.complete && !got.code && got.sections_missing==1,"host read failure has no native verdict");
    got=compare_mappings(base,{rx},{});check(!got.complete,"missing reader");
}
static void environment_tests() {
    EnvironmentCycleInput in;in.library_codes={46,46,46,46};in.tracer_pid=0;
    EnvironmentState s;auto r=run_environment_cycle(s,in);
    check(r.complete && r.ran_integrity && s.integrity_counter==1,"first cycle performs pass");
    for(unsigned i=0;i<99;++i)r=run_environment_cycle(s,in);
    check(!r.ran_integrity && s.integrity_counter==100,"99 intervening ordinary cycles");
    check(run_environment_cycle(s,in).ran_integrity,"next periodic pass");
    s={};in.library_codes={46,12,12,12};r=run_environment_cycle(s,in);
    check(r.latched==std::array<bool,4>{false,true,true,true} && !r.local_termination,"three mismatch latches");
    s.integrity_counter=100;in.library_codes={46,std::nullopt,std::nullopt,std::nullopt};
    check(run_environment_cycle(s,in).complete,"latched libraries are skipped");
    s={};in.library_codes={57,12,12,12};r=run_environment_cycle(s,in);
    check(r.local_termination && r.latched==std::array<bool,4>{true,false,false,false},"media non46 stops before other libraries");
    s={};in.library_codes={46,23,57,46};r=run_environment_cycle(s,in);
    check(!r.local_termination && r.latched==std::array<bool,4>{},"other libraries latch only 12");
    s={};in.library_codes={};check(!run_environment_cycle(s,in).complete,"missing check not silently clean");
    s={};s.latched[1]=true;in.precheck_failed=true;
    run_environment_cycle(s,in);r=run_environment_cycle(s,in);
    check(!r.local_termination && s.precheck_failures==2 && s.integrity_counter==100,"initialization retry defers pass");
    r=run_environment_cycle(s,in);check(r.local_termination && r.latched[1],"third failure preserves latches");
    s={};in.library_codes={46,46,46,46};in.precheck_failed=true;run_environment_cycle(s,in);
    in.precheck_failed=false;run_environment_cycle(s,in);check(s.precheck_failures==0,"success resets failure count");
    for(auto pid:{-1,0,1,std::numeric_limits<std::int32_t>::max(),std::numeric_limits<std::int32_t>::min()}) {
        s={};in.tracer_pid=pid;r=run_environment_cycle(s,in);
        check(r.tracer_positive==(pid>0) && r.local_termination==(pid>0),"signed tracer predicate");
    }
}
static void ime_tests() {
    InputMethodState state;auto r=evaluate_input_methods(state,{"b","a"});
    check(r.event_type==34 && r.payload==std::vector<std::string>{"b","a"},"first IME event preserves payload order");
    r=evaluate_input_methods(state,{"a","b"});check(r.kind==InputMethodResult::Kind::Unchanged && r.payload.empty(),"reorder suppressed");
    r=evaluate_input_methods(state,{"a","a","b"});check(r.event_type==35,"duplicate changes fingerprint");
    const auto saved=state.previous_hash;r=evaluate_input_methods(state,{},false);
    check(r.kind==InputMethodResult::Kind::Error && r.error_code==0xbba && state.previous_hash==saved,"JNI failure leaves IME state");
    r=evaluate_input_methods(state,{});check(r.event_type==35 && r.payload.empty(),"change to empty list");
    state={};r=evaluate_input_methods(state,{});check(r.event_type==34 && state.initialized,"first empty still emits");
    check(input_method_hash({std::string("a\0b",3)})!=input_method_hash({"a"}),"hash byte length includes embedded NUL");
}
static void integrated_existing_models() {
    EnvironmentState state;state.latched={false,true,false,true};
    check(event21_flags(state)==std::array<bool,3>{true,false,true},"event21 art/android/libc order");
    check(event24_value(state)==1,"event24 numeric art latch");
    PrismFilterFlags flags{};prism_filter_policy(false,2,0,false,10,&flags);
    check(!flags.acceptable && flags.excessive_count && flags.suspicious_handler,"seccomp policy linked");
    PrismClassOutcome outcomes[]={{1,0},{1,1},{0,0}};std::uint32_t selected[3]{};PrismClassProbeResult r{};
    prism_model_class_probe(1,1,outcomes,3,selected,&r);
    check(r.event==22 && r.selected==1 && r.cleared==1 && r.deleted==1 && selected[0]==0,"class probe linked");
}
#include "saved_digest_vectors.inc"
int main() {
    try {
        baseline_tests();mapping_tests();environment_tests();ime_tests();integrated_existing_models();saved_vector_tests();
        std::cout << "{\"result\":\"PASS\",\"checks\":" << checks << "}\n";
        return 0;
    } catch (const std::exception& e) {std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}
}
