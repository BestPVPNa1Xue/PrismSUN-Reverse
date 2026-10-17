#include "../src/accessibility_env.hpp"

#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

using prism::accessibility::ScopedJniEnvironment;
static_assert(sizeof(void*) == 8);
static_assert(offsetof(JNIInvokeInterface, AttachCurrentThread) == 0x20);
static_assert(offsetof(JNIInvokeInterface, DetachCurrentThread) == 0x28);
static_assert(offsetof(JNIInvokeInterface, GetEnv) == 0x30);
namespace {
JNIEnv synthetic_env{};
jint get_result;
jint attach_result;
std::vector<std::string> calls;
jint get_env(JavaVM*, void** out, jint version) {
    assert(version == JNI_VERSION_1_6);
    calls.push_back("GetEnv");
    *out = &synthetic_env; // deliberately non-null on failure, as in emulation
    return get_result;
}
jint attach(JavaVM*, JNIEnv** out, void* args) {
    assert(args == nullptr);
    calls.push_back("AttachCurrentThread");
    *out = &synthetic_env;
    return attach_result;
}
jint detach(JavaVM*) { calls.push_back("DetachCurrentThread"); return JNI_OK; }
struct Case {
    const char* name;
    bool null_vm;
    jint get_status;
    jint attach_status;
    bool have_env;
    bool owned;
    std::vector<std::string> expected_calls;
};
}

int main() {
    JNIInvokeInterface table{};
    table.GetEnv = get_env;
    table.AttachCurrentThread = attach;
    table.DetachCurrentThread = detach;
    JavaVM vm{&table};
    // Same external ABI cases as the original ARM64 emulation evidence.
    const std::vector<Case> cases{
        {"null_vm", true, JNI_OK, JNI_OK, false, false, {}},
        {"already_attached", false, JNI_OK, JNI_OK, true, false, {"GetEnv"}},
        {"detached_attach_success", false, JNI_EDETACHED, JNI_OK, true, true,
            {"GetEnv", "AttachCurrentThread", "DetachCurrentThread"}},
        {"detached_attach_failed", false, JNI_EDETACHED, JNI_ERR, false, false,
            {"GetEnv", "AttachCurrentThread"}},
        {"unsupported_version", false, JNI_EVERSION, JNI_OK, false, false, {"GetEnv"}},
        {"other_GetEnv_error", false, JNI_ERR, JNI_OK, false, false, {"GetEnv"}}
    };
    for (const auto& c : cases) {
        calls.clear(); get_result = c.get_status; attach_result = c.attach_status;
        {
            ScopedJniEnvironment scope(c.null_vm ? nullptr : &vm);
            assert(scope.get() == (c.have_env ? &synthetic_env : nullptr));
            assert(scope.attached_by_this_scope() == c.owned);
        }
        assert(calls == c.expected_calls);
        std::cout << "PASS " << c.name << '\n';
    }
    std::cout << "PASS: 6 env-scope scenarios match original ARM64 emulation\n";
}
