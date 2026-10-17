#include "identity.hpp"
#include <cassert>
#include <iostream>
#include <limits>
using namespace prism;
int main() {
    Session s;
    s.install(Bytes(32, 0), bytes("TEST_KEY"), 1);
    Identity id{"", false};
    AppInfo app{"APP_PACKAGE", "TEST_APK_DIGEST", {"", false}};
    assert(client_properties({}, id, app, s).kind == Result::Kind::None);
    assert(client_properties({std::nullopt}, id, app, s).kind == Result::Kind::None);
    assert(client_properties({"CHALLENGE", "EXTRA"}, id, app, s).kind == Result::Kind::None);
    assert(client_properties({"1234567"}, id, app, s).kind == Result::Kind::None);
    assert(client_properties({std::string("1234567\0EXTRA", 13)}, id, app, s).kind ==
           Result::Kind::None);
    assert(client_properties({"12345678"}, id, app, s).kind == Result::Kind::Event);
    assert(client_properties({"12345678"}, id, app, s, false).error == 3002);
    s.generation = 0;
    assert(client_properties({"12345678"}, id, app, s, false).error == 6005);
    s.generation = 1;
    assert(json_string("\n\"\\\x01") == "\"\\n\\\"\\\\\\u0001\"");
    auto result = client_properties({"CHALLENGE"}, id, app, s);
    auto record = encode_result(result, s, 0);
    assert(record && record->type == 5 && s.next_sequence == 1);
    auto record2 = encode_result(result, s, 0);
    assert(record2 && record2->payload != record->payload && s.next_sequence == 2);
    assert(!encode_result({}, s, 0));
    assert(s.next_sequence == 2);
    auto error = encode_result({Result::Kind::Error, 6005, {}}, s, 0);
    assert(error && error->type == 6 && hex(error->payload) == "75170000");
    bool caught = false;
    s.next_sequence = std::numeric_limits<std::uint64_t>::max();
    try {
        (void)encode_result(result, s, 0);
    } catch (const std::overflow_error &) {
        caught = true;
    }
    assert(caught);
    s.install(Bytes(32, 1), bytes("ANOTHER_TEST_KEY"), 2);
    assert(s.next_sequence == 0 && s.generation == 2);
    caught = false;
    try {
        (void)encrypt_packet({}, Bytes(31), 1, 0, 0);
    } catch (const std::invalid_argument &) {
        caught = true;
    }
    assert(caught);
    caught = false;
    try {
        (void)first_v2_certificate({});
    } catch (const std::runtime_error &) {
        caught = true;
    }
    assert(caught);
    std::cout << "PASS: input cardinality/type/NUL, error order, JSON escaping, sequence, invalid "
                 "key/APK\n";
}
