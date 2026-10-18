#pragma once
#include <array>
#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

// Semantic reconstruction of PSR_20250811.531a9c4, not original source.
namespace prism_old {
inline constexpr std::array<const char*,7> paths{{
 "/guestOSInfo", "/system/priv-app/vmos-pro-intent", "/system/priv-app/romex",
 "/sdcard/vphone_space", "/system/app/Superuser", "/system/priv-app/Superuser",
 "/data/app/VPhoneQuickHelp"}};
struct PathResult { int first=-1; unsigned attempted=0; bool hit() const { return first>=0; } };
PathResult probe_paths(const std::function<int(const char*)>& stat_call);
struct MapsState { std::uint32_t baseline16=0, named20=0, anonymous24=0; };
struct MapsResult {
 bool opened=true, incomplete=false;
 // The successful reader leaves this empty; the error path appends a diagnostic.
 std::vector<std::string> diagnostics;
};
MapsResult parse_maps(std::string_view bytes, MapsState&, std::optional<int> initial_n={});
MapsResult maps_open_error(MapsState&);
struct DebugResult {
 int value=-1; bool parse_error=false; int abnormal_reason=0;
 bool positive() const { return value>0; }
};
DebugResult parse_status(std::string_view bytes);
DebugResult status_open_result(int fd);
bool entry_guard(std::array<std::uint32_t,3> words);

// Android/POSIX acquisition. No worker thread or process-termination backend.
PathResult probe_paths_native();
MapsResult read_maps_native(MapsState&);
DebugResult read_status_native();
}
