#pragma once

#include <cstdint>

#if defined(_WIN32)
#define PRISM_PROBE_API __declspec(dllexport)
#else
#define PRISM_PROBE_API __attribute__((visibility("default")))
#endif

struct PrismClassOutcome {
    std::uint8_t found;
    std::uint8_t exception;
};

struct PrismClassProbeResult {
    std::uint32_t queried;
    std::uint32_t selected;
    std::uint32_t cleared;
    std::uint32_t deleted;
    std::uint32_t event;
    std::uint32_t acquisition_failed;
};

// The caller supplies count outcomes and count writable selected-index slots.
// JNI acquisition, class lookup, configuration and object ABI are external.
extern "C" PRISM_PROBE_API void prism_model_class_probe(
    std::uint8_t configured, std::uint8_t environment_ready,
    const PrismClassOutcome* outcomes, std::uint32_t count,
    std::uint32_t* selected_indices, PrismClassProbeResult* output) noexcept;
