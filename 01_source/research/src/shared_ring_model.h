#pragma once

#include <cstdint>

#if defined(_WIN32)
#define PRISM_RING_API __declspec(dllexport)
#else
#define PRISM_RING_API __attribute__((visibility("default")))
#endif

enum class PrismRingStatus : std::uint32_t {
    Empty = 0,
    InvalidSlots = 1,
    InvalidLength = 2,
    Incomplete = 3,
    Ready = 4,
};

struct PrismRingPlan {
    PrismRingStatus status;
    std::uint32_t next_read;
    std::uint32_t declared_size;
    std::uint32_t copied_size;
    std::uint8_t type;
    std::uint8_t slot_count;
    std::uint8_t resize_required;
    std::uint8_t reserved;
    std::uint16_t chunks[16];
};

// slots is a stable 65536-byte snapshot, excluding the two shared counters.
// This structure is a semantic model, not the original optional/string ABI.
extern "C" PRISM_RING_API void prism_plan_ring_read(
    std::uint32_t writer, std::uint32_t reader,
    const std::uint8_t* slots, PrismRingPlan* output) noexcept;
