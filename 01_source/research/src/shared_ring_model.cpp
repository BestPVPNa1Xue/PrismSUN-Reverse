#include "shared_ring_model.h"

namespace {
std::uint16_t read_u16(const std::uint8_t* bytes) noexcept {
    return static_cast<std::uint16_t>(bytes[0]) |
           static_cast<std::uint16_t>(bytes[1] << 8);
}

std::uint32_t read_u32(const std::uint8_t* bytes) noexcept {
    return static_cast<std::uint32_t>(bytes[0]) |
           (static_cast<std::uint32_t>(bytes[1]) << 8) |
           (static_cast<std::uint32_t>(bytes[2]) << 16) |
           (static_cast<std::uint32_t>(bytes[3]) << 24);
}
}

void prism_plan_ring_read(std::uint32_t writer, std::uint32_t reader,
                          const std::uint8_t* slots,
                          PrismRingPlan* output) noexcept {
    *output = {};
    output->next_read = reader;
    if (writer == reader) {
        output->status = PrismRingStatus::Empty;
        return;
    }
    const auto* first = slots + (reader & 15u) * 4096u;
    output->declared_size = read_u32(first);
    output->type = first[4];
    output->slot_count = first[5];
    if (output->slot_count == 0 || output->slot_count > 16) {
        output->status = PrismRingStatus::InvalidSlots;
        output->next_read = writer;
        return;
    }
    if (output->declared_size > 0xff80u) {
        output->status = PrismRingStatus::InvalidLength;
        output->next_read = writer;
        return;
    }
    const std::uint32_t available = writer - reader;
    if (available < output->slot_count) {
        output->status = PrismRingStatus::Incomplete;
        return;
    }
    for (std::uint32_t index = 0; index < output->slot_count; ++index) {
        const auto* slot = slots + ((reader + index) & 15u) * 4096u;
        const auto length = read_u16(slot + 6);
        output->chunks[index] = length > 0xff8u ? 0xff8u : length;
        output->copied_size += output->chunks[index];
    }
    output->resize_required = output->copied_size != output->declared_size;
    output->next_read = reader + output->slot_count;
    output->status = PrismRingStatus::Ready;
}
