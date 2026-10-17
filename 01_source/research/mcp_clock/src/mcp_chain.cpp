#include "mcp_chain.hpp"
#include <array>
#include <stdexcept>
#ifndef _WIN32
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>
#endif

namespace prism::mcp {
bool ends_with(std::string_view value, std::string_view suffix) {
    return value.size() >= suffix.size() && value.substr(value.size()-suffix.size()) == suffix;
}
bool starts_with(std::string_view value, std::string_view prefix) {
    return value.size() >= prefix.size() && value.substr(0, prefix.size()) == prefix;
}
ParsedText parse_file(FileOps& fs, const std::string& path) {
    // 0x30e700. The decoded comparison is JDWL; raw file bytes are MCPK.
    const int fd = fs.open_read(path);
    if (fd < 0) return {ParseStatus::OpenFailed, {}, false};
    struct Close { FileOps& fs; int fd; ~Close() { fs.close(fd); } } close{fs,fd};
    std::array<std::uint8_t,4> header{};
    const auto n = fs.read(fd, header.data(), header.size());
    constexpr std::array<std::uint8_t,4> magic{'J','D','W','L'};
    // The original ignores read() results. Known mismatches are deterministic;
    // missing initial bytes are not silently treated as zero in this model.
    for (std::size_t i=0; i<4; ++i) {
        if (n <= static_cast<std::int64_t>(i))
            return {ParseStatus::IndeterminateStack, {}, true};
        if ((header[i]^7) != magic[i]) return {ParseStatus::WrongMagic, {}, n!=4};
    }
    ParsedText out;
    out.ignored_io_failure = fs.seek(fd,24) < 0; // original ignores lseek result
    std::uint8_t byte = 0;
    bool have_byte = false;
    for (unsigned i=0; i<64; ++i) {
        const auto got = fs.read(fd,&byte,1);
        if (got == 1) have_byte = true;
        else {
            out.ignored_io_failure = true;
            if (!have_byte) { out.status=ParseStatus::IndeterminateStack; return out; }
            // EOF/error leaves the preceding byte in the original stack slot.
        }
        if (byte == 0) break;
        out.text.push_back(static_cast<char>(byte));
    }
    return out;
}
Scan collect(FileOps& fs, std::uint32_t pid) {
    Scan out;
    out.directory="/proc/"+std::to_string(pid)+"/fd";
    constexpr std::string_view marker="/PrismSUNScripts.mcp";
    // 0x30bb2c, first independent open and enumeration.
    out.first_directory_open=fs.enumerate(out.directory,[&](const Entry& e) {
        if(e.type!=10) return true;
        const auto target=fs.readlink(out.directory+"/"+e.name);
        if(!target || !ends_with(*target,marker)) return true;
        const auto pos=target->find(marker);
        // The SUB X2,X8,#1 at 0x30bf80 is real, not a typo to repair.
        out.prefix=target->substr(0,pos-std::size_t{1});
        out.marker_found=true;
        return false;
    });
    // 0x30b278. Empty prefix passes starts_with, even if the first open failed.
    out.second_directory_open=fs.enumerate(out.directory,[&](const Entry& e) {
        if(e.type!=10) return true;
        auto target=fs.readlink(out.directory+"/"+e.name);
        if(!target || !ends_with(*target,".mcp") || !starts_with(*target,out.prefix)) return true;
        auto parsed=parse_file(fs,*target);
        if(!parsed.complete()) { ++out.indeterminate_files; return true; }
        const auto slash=target->rfind('/');
        out.values.push_back(target->substr(slash+std::size_t{1})+":"+parsed.text);
        return true; // order and duplicates are preserved
    });
    return out;
}
std::string json_string(std::string_view value) {
    constexpr char hex[]="0123456789abcdef";
    std::string out="\"";
    for(unsigned char c:value) {
        switch(c) {
        case '"': out+="\\\""; break; case '\\': out+="\\\\"; break;
        case '\b': out+="\\b"; break; case '\f': out+="\\f"; break;
        case '\n': out+="\\n"; break; case '\r': out+="\\r"; break;
        case '\t': out+="\\t"; break;
        default: if(c<32) { out+="\\u00";out+=hex[c>>4];out+=hex[c&15]; }
                 else out+=static_cast<char>(c);
        }
    }
    return out+'"';
}
std::optional<std::string> event32_payload(const Scan& scan) {
    if(!scan.complete()) return std::nullopt;
    std::string out="[";
    for(const auto& s:scan.values) { if(out.size()>1) out+=',';out+=json_string(s); }
    return out+"]";
}
#ifndef _WIN32
bool NativeFiles::enumerate(const std::string& path,const std::function<bool(const Entry&)>& visit) {
    const int fd=static_cast<int>(::syscall(SYS_openat,AT_FDCWD,path.c_str(),O_RDONLY|O_DIRECTORY,0));
    if(fd<0) return false;
    DIR* dir=::fdopendir(fd);
    if(!dir) { ::close(fd);return false; }
    struct Close { DIR* dir; ~Close(){::closedir(dir);} } close{dir};
    while(auto* ent=::readdir(dir)) if(!visit({ent->d_name,ent->d_type})) break;
    return true;
}
std::optional<std::string> NativeFiles::readlink(const std::string& path) {
    // Extra byte removes the original out-of-bounds terminator at length 4096.
    std::array<char,4097> b{};
    const auto n=::syscall(SYS_readlinkat,AT_FDCWD,path.c_str(),b.data(),4096);
    if(n<0) return std::nullopt;
    b[static_cast<std::size_t>(n)]=0;
    return std::string(b.data());
}
int NativeFiles::open_read(const std::string& path) {
    return static_cast<int>(::syscall(SYS_openat,AT_FDCWD,path.c_str(),O_RDONLY,0));
}
std::int64_t NativeFiles::read(int fd,void* p,std::size_t n){return ::syscall(SYS_read,fd,p,n);}
std::int64_t NativeFiles::seek(int fd,std::int64_t n){return ::syscall(SYS_lseek,fd,n,SEEK_SET);}
void NativeFiles::close(int fd){::syscall(SYS_close,fd);}
#else
static void unsupported(){throw std::runtime_error("Native /proc fd scanning requires Linux/Android; use FileOps fixtures on Windows");}
bool NativeFiles::enumerate(const std::string&,const std::function<bool(const Entry&)>&){unsupported();return false;}
std::optional<std::string> NativeFiles::readlink(const std::string&){unsupported();return {};}
int NativeFiles::open_read(const std::string&){unsupported();return -1;}
std::int64_t NativeFiles::read(int,void*,std::size_t){unsupported();return -1;}
std::int64_t NativeFiles::seek(int,std::int64_t){unsupported();return -1;}
void NativeFiles::close(int){unsupported();}
#endif
} // namespace prism::mcp
