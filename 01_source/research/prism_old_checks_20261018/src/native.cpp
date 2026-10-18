#include "../include/prism_old.hpp"
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <unistd.h>

namespace prism_old {
PathResult probe_paths_native() {
 return probe_paths([](const char* path) {
  struct stat st{};
  return static_cast<int>(syscall(SYS_newfstatat,AT_FDCWD,path,&st,0));
 });
}
MapsResult read_maps_native(MapsState& state) {
 const int fd=open("/proc/self/maps",O_RDONLY);
 if(fd<0)return maps_open_error(state);
 FILE* stream=fdopen(fd,"r");
 if(!stream) { close(fd);auto r=maps_open_error(state);r.incomplete=true;return r; }
 std::string text;char* line=nullptr;std::size_t cap=0;ssize_t n;
 while((n=getline(&line,&cap,stream))>0)text.append(line,static_cast<std::size_t>(n));
 const bool io_error=ferror(stream)!=0;free(line);fclose(stream);
 auto r=parse_maps(text,state);r.incomplete=r.incomplete||io_error;return r;
}
DebugResult read_status_native() {
 const int fd=open("/proc/self/status",O_RDONLY);
 if(fd<=0) { auto r=status_open_result(fd);if(fd==0)close(fd);return r; }
 FILE* stream=fdopen(fd,"r");
 if(!stream) { close(fd);DebugResult r;r.parse_error=true;return r; }
 std::string text;char line[512];
 while(fgets(line,sizeof(line),stream))text+=line;
 const bool io_error=ferror(stream)!=0;fclose(stream);
 auto r=parse_status(text);r.parse_error=r.parse_error||io_error;return r;
}
}
