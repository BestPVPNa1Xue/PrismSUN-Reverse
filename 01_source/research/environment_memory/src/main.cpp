#include "environment_memory.hpp"
#include <fstream>
#include <iostream>
#include <iterator>

int main(int argc, char** argv) {
    using namespace prism::environment;
    if (argc != 2) {
        std::cerr << "Usage: prism_environment <offline ELF64 AArch64 file>\n";
        return 2;
    }
    std::ifstream file(argv[1], std::ios::binary);
    if (!file) { std::cerr << "Cannot open input\n"; return 2; }
    const std::vector<std::uint8_t> bytes((std::istreambuf_iterator<char>(file)), {});
    const auto baseline = make_elf_baseline(bytes);
    if (!baseline) { std::cerr << "Invalid or unsupported ELF\n"; return 1; }
    std::cout << "Offline section baseline; not a live-process integrity verdict\n";
    for (const auto& s : baseline->sections)
        std::cout << "section=" << s.index << " offset=" << s.file_offset
                  << " size=" << s.size << " crc32_bswap=" << s.digest_xor_mask << '\n';
    return baseline->initialized ? 0 : 1;
}
