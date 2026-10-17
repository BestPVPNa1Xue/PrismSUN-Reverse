#include "verified_helpers.h"

#include <array>
#include <cstring>
#include <iostream>

int main() {
    std::array<std::uint8_t, 8> ciphertext{
        0x75, 0x92, 0x2f, 0x9d, 0xd6, 0x59, 0x12, 0xa1};
    const auto original = ciphertext;
    prism_xor_cycle64(ciphertext.data(), ciphertext.size(), 0xa12f2bb3e943fb13ULL);
    if (std::memcmp(ciphertext.data(), "filter=", 8) != 0) return 1;
    prism_xor_cycle64(ciphertext.data(), ciphertext.size(), 0xa12f2bb3e943fb13ULL);
    if (ciphertext != original) return 2;
    const std::array<std::uint8_t, 4> input{0x00, 0x0f, 0xa1, 0xff};
    std::array<char, 9> output{};
    output.back() = '!';
    prism_hex_encode(output.data(), input.data(), input.size(), true);
    if (std::memcmp(output.data(), "000FA1FF!", 9) != 0) return 3;
    prism_hex_encode(output.data(), input.data(), input.size(), false);
    if (std::memcmp(output.data(), "000fa1ff!", 9) != 0) return 4;
    if (!prism_entry_pattern(0x14000000u, 0, 0)) return 5;
    if (!prism_entry_pattern(0xd4200020u, 0, 0)) return 6;
    if (!prism_entry_pattern(0, 0xd61f0200u, 0)) return 7;
    if (!prism_entry_pattern(0, 0, 0xd61f03e0u)) return 8;
    if (prism_entry_pattern(0xa9bf7bfdu, 0x910003fdu, 0xd503201fu)) return 9;
    prism_xor_cycle64(nullptr, 0, 0);
    prism_hex_encode(nullptr, nullptr, 0, false);
    std::cout << "9 checks passed; zero-length calls completed\n";
}
