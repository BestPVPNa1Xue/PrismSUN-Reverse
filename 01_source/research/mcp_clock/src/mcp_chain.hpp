#pragma once
#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace prism::mcp {
struct Entry { std::string name; std::uint8_t type; };
class FileOps {
public:
    virtual ~FileOps() = default;
    // Return false if open/fdopendir fails. Visitor false stops enumeration.
    virtual bool enumerate(const std::string&, const std::function<bool(const Entry&)>&) = 0;
    virtual std::optional<std::string> readlink(const std::string&) = 0;
    virtual int open_read(const std::string&) = 0;
    virtual std::int64_t read(int, void*, std::size_t) = 0;
    virtual std::int64_t seek(int, std::int64_t) = 0;
    virtual void close(int) = 0;
};
class NativeFiles final : public FileOps {
public:
    bool enumerate(const std::string&, const std::function<bool(const Entry&)>&) override;
    std::optional<std::string> readlink(const std::string&) override;
    int open_read(const std::string&) override;
    std::int64_t read(int, void*, std::size_t) override;
    std::int64_t seek(int, std::int64_t) override;
    void close(int) override;
};
enum class ParseStatus { Parsed, OpenFailed, WrongMagic, IndeterminateStack };
struct ParsedText {
    ParseStatus status = ParseStatus::Parsed;
    std::string text;
    bool ignored_io_failure = false;
    bool complete() const { return status != ParseStatus::IndeterminateStack; }
};
struct Scan {
    std::string directory, prefix;
    bool marker_found = false;
    bool first_directory_open = false, second_directory_open = false;
    std::size_t indeterminate_files = 0;
    std::vector<std::string> values;
    bool complete() const { return indeterminate_files == 0; }
};
bool ends_with(std::string_view, std::string_view);
bool starts_with(std::string_view, std::string_view);
ParsedText parse_file(FileOps&, const std::string&);
Scan collect(FileOps&, std::uint32_t pid);
// Event 32 always exists, including an empty array, for a determinate scan.
// nullopt means original uninitialized stack bytes prevent a defined result.
std::optional<std::string> event32_payload(const Scan&);
std::string json_string(std::string_view);
} // namespace prism::mcp
