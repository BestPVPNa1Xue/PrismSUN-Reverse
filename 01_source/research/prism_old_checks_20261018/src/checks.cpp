#include "../include/prism_old.hpp"
#include <cstdio>
#include <stdexcept>

namespace prism_old {
PathResult probe_paths(const std::function<int(const char*)>& stat_call) {
 PathResult r;
 for (unsigned i=0;i<paths.size();++i) {
  ++r.attempted;
  if (stat_call(paths[i])==0) { r.first=static_cast<int>(i); break; }
 }
 return r;
}
static bool space(unsigned char c) { return c==32 || (c>=9 && c<=13); }
MapsResult parse_maps(std::string_view bytes,MapsState& s,std::optional<int> initial_n) {
 MapsResult result; s.named20=0; std::uint32_t named=0,anon=0;
 auto previous_n=initial_n;
 while (!bytes.empty()) {
  auto end=bytes.find('\n'); auto size=end==bytes.npos?bytes.size():end+1;
  std::string line(bytes.substr(0,size)); bytes.remove_prefix(size);
  line.back()='\0'; // Original getline path removes the last byte unconditionally.
  unsigned long long start=0,stop=0,offset=0,inode=0;
  unsigned major=0,minor=0; char perms[5]{}; int n=-1;
  const int fields=std::sscanf(line.c_str(),"%llx-%llx %4s %llx %x:%x %llu %n%*s",
    &start,&stop,perms,&offset,&major,&minor,&inode,&n);
  if (fields<6) continue;
  if (n>=0) previous_n=n;
  // Original %n is stale/uninitialized on a six-field record. Model it explicitly.
  if (!previous_n || *previous_n<0 || static_cast<std::size_t>(*previous_n)>=line.size()) {
   result.incomplete=true; continue;
  }
  auto pos=static_cast<std::size_t>(*previous_n);
  while(pos<line.size() && space(static_cast<unsigned char>(line[pos])))++pos;
  if (pos>=line.size()) { result.incomplete=true;continue; }
  if(perms[2]!='x')continue;
  const std::string_view path(line.c_str()+pos);
  if(path.empty() || path.find("/dev/zero (deleted)")!=path.npos || path.substr(0,6)=="[anon:") {
   if(static_cast<std::uint64_t>(stop-start)>0x5000) {
    if(path.empty())++anon;else ++named;
   }
  }
 }
 s.named20=named-s.baseline16; s.anonymous24=anon;
 return result;
}
MapsResult maps_open_error(MapsState& s) {
 s.named20=0; // +24 is deliberately retained.
 MapsResult r;r.opened=false;r.diagnostics.push_back("8)");return r;
}
DebugResult parse_status(std::string_view bytes) {
 DebugResult result;
 while(!bytes.empty()) {
  auto newline=bytes.find('\n');
  std::size_t n=newline==bytes.npos?bytes.size():newline+1;
  if(n>511)n=511; // The original inlined reader has a 512-byte buffer.
  std::string line(bytes.substr(0,n));bytes.remove_prefix(n);
  line.resize(line.find('\0')==line.npos?line.size():line.find('\0'));
  try {
   if(line.find("TracerPid:")!=line.npos) {
    result.value=std::stoi(line.substr(11),nullptr,10);return result;
   }
   if(line.find("State:")!=line.npos) {
    const auto suffix=line.substr(7);
    if(suffix=="t" || suffix=="(tracing stop)") { result.value=6;return result; }
   }
  } catch(const std::invalid_argument&) { result.parse_error=true;return result; }
    catch(const std::out_of_range&) { result.parse_error=true;return result; }
 }
 return result;
}
DebugResult status_open_result(int fd) {
 DebugResult r;if(fd<=0)r.abnormal_reason=5;return r;
}
bool entry_guard(std::array<std::uint32_t,3> w) {
 return (w[0]>>26)==5 || (w[0]>>21)==1697 ||
   (w[1]>>10)==3508160 || (w[2]>>10)==3508160;
}
}
