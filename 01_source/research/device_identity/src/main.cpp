#include "identity.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace prism;
namespace {
std::string string_from_hex(const char *v) {
    auto b = unhex(v);
    return std::string(b.begin(), b.end());
}
std::string digest_hex(const Digest &d) {
    return hex(Bytes(d.begin(), d.end()));
}
void output_result(const Result &r) {
    std::cout << "{\"kind\":" << static_cast<int>(r.kind) << ",\"error\":" << r.error;
    if (r.kind == Result::Kind::Event)
        std::cout << ",\"event_type\":19,\"payload\":" << r.payload_json;
    std::cout << "}\n";
}
} // namespace
int main(int argc, char **argv) {
    try {
        std::string cmd = argc > 1 ? argv[1] : "demo";
        if (cmd == "sha" && argc == 3)
            std::cout << digest_hex(sha256(unhex(argv[2]))) << '\n';
        else if (cmd == "hmac" && argc == 4)
            std::cout << digest_hex(hmac_sha256(unhex(argv[2]), unhex(argv[3]))) << '\n';
        else if (cmd == "drm" && argc == 3)
            std::cout << drm_id(unhex(argv[2])) << '\n';
        else if (cmd == "boot" && argc == 3)
            std::cout << boot_id(string_from_hex(argv[2])) << '\n';
        else if (cmd == "salted" && argc == 3)
            std::cout << salted_id(string_from_hex(argv[2])) << '\n';
        else if (cmd == "packet" && argc == 7)
            std::cout << hex(encrypt_packet(unhex(argv[2]), unhex(argv[3]),
                                            static_cast<std::uint16_t>(std::stoul(argv[4])),
                                            std::stoull(argv[5]),
                                            static_cast<std::uint8_t>(std::stoul(argv[6]))))
                      << '\n';
        else if (cmd == "event" && argc == 7) {
            Session s;
            s.hmac_key = bytes("TEST_KEY");
            s.generation = static_cast<std::uint16_t>(std::stoul(argv[6]));
            auto primary = string_from_hex(argv[3]);
            auto fallback = string_from_hex(argv[4]);
            Identity id = {primary.empty() ? fallback : primary, !primary.empty()};
            output_result(
                client_properties({string_from_hex(argv[2])}, id,
                                  {"APP_PACKAGE", "TEST_APK_DIGEST", {"TARGET_ACTIVITY", true}}, s,
                                  std::stoi(argv[5]) != 0));
        } else if (cmd == "activities") {
            std::vector<std::string> names;
            for (int i = 2; i < argc; ++i)
                names.emplace_back(argv[i]);
            auto r = activity_info(names);
            std::cout << '[' << json_string(r.wx_prefix) << ',' << (r.has_mpay ? "true" : "false")
                      << "]\n";
        } else if (cmd == "certificate" && argc == 3)
            std::cout << hex(first_v2_certificate(unhex(argv[2]))) << '\n';
        else if (cmd == "ring" && argc == 7) {
            Ring ring;
            auto head = std::stoul(argv[3]), tail = std::stoul(argv[4]);
            for (unsigned i = 0; i < 4; ++i) {
                ring.memory[i] = static_cast<std::uint8_t>(head >> (8 * i));
                ring.memory[i + 4] = static_cast<std::uint8_t>(tail >> (8 * i));
            }
            bool ok = ring.write({static_cast<std::uint8_t>(std::stoul(argv[2])), unhex(argv[5])});
            std::ofstream file(argv[6], std::ios::binary);
            file.write(reinterpret_cast<const char *>(ring.memory.data()), ring.memory.size());
            if (!file)
                throw std::runtime_error("write failed");
            std::cout << (ok ? "1" : "0") << '\n';
        } else if (cmd == "demo") {
            Session s;
            Bytes key(32);
            for (unsigned i = 0; i < 32; ++i)
                key[i] = static_cast<std::uint8_t>(i);
            s.install(key, bytes("TEST_KEY"), 0x1234);
            s.next_sequence = 7;
            auto id = choose_identity(unhex("0001FEFF"), "TEST_BOOT_ID");
            auto result =
                client_properties({"CHALLENGE"}, id,
                                  {"APP_PACKAGE", "TEST_APK_DIGEST", {"TARGET_ACTIVITY", true}}, s);
            output_result(result);
            auto record = encode_result(result, s, 10);
            Ring ring;
            std::cout << "{\"record_type\":" << unsigned(record->type)
                      << ",\"packet_hex\":" << json_string(hex(record->payload))
                      << ",\"ring_write\":" << (ring.write(*record) ? "true" : "false")
                      << ",\"next_sequence\":" << s.next_sequence << "}\n";
        } else
            throw std::invalid_argument(
                "usage: prism_identity [demo|sha HEX|hmac KEYHEX MSGHEX|drm HEX|boot HEX|salted "
                "HEX|packet MSGHEX KEYHEX GENERATION SEQUENCE NIBBLE|event CHALLENGEHEX PRIMARYHEX "
                "FALLBACKHEX JNI_OK READY|activities NAME...|certificate APKHEX|ring TYPE HEAD "
                "TAIL HEX OUTPUT]");
        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
