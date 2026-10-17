#include "accessibility_core.hpp"
#include <iomanip>
#include <iostream>

int main(int argc, char** argv) {
    using namespace prism::accessibility;
    State state;
    std::vector<std::string> ids(argv + 1, argv + argc);
    for (int i = 0; i < 2; ++i) {
        const auto r = evaluate(state, ids);
        std::cout << "kind=" << static_cast<unsigned>(r.kind)
                  << " event=" << static_cast<unsigned>(r.event_type)
                  << " hash=0x" << std::hex << std::setw(8) << std::setfill('0')
                  << state.previous_hash.load() << std::dec
                  << " payload=" << payload_json(r) << '\n';
    }
}
