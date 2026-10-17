#include "class_probe_model.h"

extern "C" PRISM_PROBE_API void prism_model_class_probe(
    std::uint8_t configured, std::uint8_t environment_ready,
    const PrismClassOutcome* outcomes, std::uint32_t count,
    std::uint32_t* selected_indices, PrismClassProbeResult* output) noexcept {
    *output = {};
    if ((configured & 1u) == 0) {
        output->event = 22;
        return;
    }
    if ((environment_ready & 1u) == 0) {
        output->acquisition_failed = 1;
        return;
    }
    for (std::uint32_t index = 0; index < count; ++index) {
        ++output->queried;
        if (outcomes[index].exception != 0) {
            ++output->cleared;
            continue;
        }
        if (outcomes[index].found != 0) {
            ++output->deleted;
            selected_indices[output->selected++] = index;
        }
    }
    output->event = 22;
}
