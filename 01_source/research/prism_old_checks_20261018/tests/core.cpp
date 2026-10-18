#include "../include/prism_old.hpp"
#include <cassert>
#include <iostream>
using namespace prism_old;
int main(){
unsigned checks=0;
{ auto r=parse_status("TracerPid:\t0\n");
assert(!r.parse_error && r.value==0);
(void)r;++checks; }
{ auto r=parse_status("TracerPid:\t123\n");
assert(!r.parse_error && r.value==123);
(void)r;++checks; }
{ auto r=parse_status("State:\tt (tracing stop)\nTracerPid:\t9\n");
assert(!r.parse_error && r.value==9);
(void)r;++checks; }
{ auto r=parse_status("State:\tt\nTracerPid:\t9\n");
assert(!r.parse_error && r.value==9);
(void)r;++checks; }
{ auto r=parse_status("State:\tt");
assert(!r.parse_error && r.value==6);
(void)r;++checks; }
{ auto r=parse_status("State:\t(tracing stop)");
assert(!r.parse_error && r.value==6);
(void)r;++checks; }
{ auto r=parse_status("State:\tS (sleeping)\n");
assert(!r.parse_error && r.value==-1);
(void)r;++checks; }
{ auto r=parse_status("");
assert(!r.parse_error && r.value==-1);
(void)r;++checks; }
{ auto r=parse_status("");
assert(status_open_result(0).abnormal_reason==5);
(void)r;++checks; }
{ auto r=parse_status("");
assert(status_open_result(-1).abnormal_reason==5);
(void)r;++checks; }
{ auto r=parse_status("xxTracerPid:\t9\n");
assert(r.parse_error);
(void)r;++checks; }
{ auto r=parse_status("TracerPid:\tbad\n");
assert(r.parse_error);
(void)r;++checks; }
{ MapsState state{0,99,77};
auto r=parse_maps("",state,0);assert(r.opened);
assert(state.named20==0u && state.anonymous24==0u);++checks;}
{ MapsState state{3,99,77};
auto r=parse_maps("",state,0);assert(r.opened);
assert(state.named20==4294967293u && state.anonymous24==0u);++checks;}
{ MapsState state{3,99,77};
auto r=maps_open_error(state);assert(!r.opened);
assert(state.named20==0u && state.anonymous24==77u);++checks;}
{ MapsState state{0,99,77};
auto r=parse_maps("1000-7000 r-xp 0 00:00 0\n",state,0);assert(r.opened);
assert(state.named20==0u && state.anonymous24==1u);++checks;}
{ MapsState state{0,99,77};
auto r=parse_maps("1000-6000 r-xp 0 00:00 0\n",state,0);assert(r.opened);
assert(state.named20==0u && state.anonymous24==0u);++checks;}
{ MapsState state{0,99,77};
auto r=parse_maps("1000-7000 rw-p 0 00:00 0\n",state,0);assert(r.opened);
assert(state.named20==0u && state.anonymous24==0u);++checks;}
{ MapsState state{0,99,77};
auto r=parse_maps("1000-7000 r-xp 0 00:00 0 /dev/zero (deleted)\n",state,0);assert(r.opened);
assert(state.named20==1u && state.anonymous24==0u);++checks;}
{ MapsState state{2,99,77};
auto r=parse_maps("1000-7000 r-xp 0 00:00 0 [anon:dalvik]\n",state,0);assert(r.opened);
assert(state.named20==4294967295u && state.anonymous24==0u);++checks;}
{ MapsState state{0,99,77};
auto r=parse_maps("1000-7000 r-xp 0 00:00 0 /data/app/a.so\n",state,0);assert(r.opened);
assert(state.named20==0u && state.anonymous24==0u);++checks;}
{ MapsState state{0,99,77};
auto r=parse_maps("1000-7000 r-xp 0 00:00 0 [anon:",state,0);assert(r.opened);
assert(state.named20==0u && state.anonymous24==0u);++checks;}
{ MapsState state{0,99,77};
auto r=parse_maps("7000-1000 r-xp 0 00:00 0\n",state,0);assert(r.opened);
assert(state.named20==0u && state.anonymous24==1u);++checks;}
{ MapsState state{0,99,77};
auto r=parse_maps("1000-7000 r-xp 0 00:00 X\n",state,0);assert(r.opened);
assert(state.named20==0u && state.anonymous24==0u);++checks;}
for(int hit=-1;hit<7;++hit){int at=0;auto r=probe_paths([&](const char* p){assert(std::string(p)==paths[at]);return at++==hit?0:-1;});assert(r.first==hit);assert(r.attempted==static_cast<unsigned>(hit<0?7:hit+1));++checks;}
assert(entry_guard({0x14000000,0,0}));assert(entry_guard({0xd4200000,0,0}));assert(entry_guard({0,0xd61f0020,0}));assert(!entry_guard({0x94000000,0,0}));checks+=4;
auto malformed=parse_status("TracerPid:\t99999999999999999999999\n");assert(malformed.parse_error);++checks;
MapsState partial;auto missing=parse_maps("1000-7000 r-xp 0 00:00 X\n",partial);assert(missing.incomplete);++checks;
std::cout<<"{\"core_assertion_groups\":"<<checks<<",\"result\":\"PASS\"}\n";
}