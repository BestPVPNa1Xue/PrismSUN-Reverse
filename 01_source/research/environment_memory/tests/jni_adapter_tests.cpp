// Adapted from the previously verified accessibility JNI mock fixture.
// No Android framework or original binary executes in this test.
#include "../src/input_methods_jni.hpp"

#include <cassert>
#include <cstddef>
#include <cstdarg>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace prism::environment;
static_assert(sizeof(void*) == 8, "These table offsets describe the ARM64 sample");
static_assert(offsetof(JNINativeInterface, FindClass) == 0x30);
static_assert(offsetof(JNINativeInterface, DeleteLocalRef) == 0xb8);
static_assert(offsetof(JNINativeInterface, GetMethodID) == 0x108);
static_assert(offsetof(JNINativeInterface, CallObjectMethodV) == 0x118);
static_assert(offsetof(JNINativeInterface, CallIntMethodV) == 0x190);
static_assert(offsetof(JNINativeInterface, GetStaticMethodID) == 0x388);
static_assert(offsetof(JNINativeInterface, CallStaticObjectMethodV) == 0x398);
static_assert(offsetof(JNINativeInterface, GetStaticFieldID) == 0x480);
static_assert(offsetof(JNINativeInterface, GetStaticObjectField) == 0x488);
static_assert(offsetof(JNINativeInterface, GetStringUTFChars) == 0x548);
static_assert(offsetof(JNINativeInterface, ReleaseStringUTFChars) == 0x550);
namespace {
enum Method : std::uintptr_t { Current = 1, Application, SystemService, Enabled, Get, Size, Id };
constexpr std::uintptr_t kContext = 10, kThread = 11, kManager = 12, kList = 13, kService = 14;
struct State {
    std::vector<std::string> ids{"fixture/.A", "fixture/.B", "fixture/.A"};
    std::map<jobject, int> live;
    std::set<int> null_id;
    std::set<int> null_chars;
    int fail_id = -1;
    int manager_calls = 0;
    int release_count = 0;
    int size_calls = 0;
    int find_calls = 0;
    bool exception = false;
    bool null_list = false;
} state;
template <typename T> T ptr(std::uintptr_t n) { return reinterpret_cast<T>(n); }
std::uintptr_t value(jobject o) { return reinterpret_cast<std::uintptr_t>(o); }
template <typename T> T local(T o) { if (o) ++state.live[o]; return o; }
jclass find_class(JNIEnv*, const char* name) {
    ++state.find_calls;
    static const std::map<std::string, std::uintptr_t> classes{
        {"android/app/ActivityThread", 20}, {"android/content/Context", 21},
        {"android/view/inputmethod/InputMethodManager", 22},
        {"java/util/List", 23}, {"android/view/inputmethod/InputMethodInfo", 24}};
    assert(classes.count(name));
    return local(ptr<jclass>(classes.at(name)));
}
jmethodID method(JNIEnv*, jclass, const char* name, const char* signature) {
    static const std::map<std::string, std::pair<Method, std::string>> methods{
        {"currentActivityThread", {Current, "()Landroid/app/ActivityThread;"}},
        {"getApplication", {Application, "()Landroid/app/Application;"}},
        {"getSystemService", {SystemService, "(Ljava/lang/String;)Ljava/lang/Object;"}},
        {"getInputMethodList", {Enabled, "()Ljava/util/List;"}},
        {"get", {Get, "(I)Ljava/lang/Object;"}}, {"size", {Size, "()I"}},
        {"getServiceName", {Id, "()Ljava/lang/String;"}}};
    assert(methods.count(name));
    assert(methods.at(name).second == signature);
    return ptr<jmethodID>(methods.at(name).first);
}
jfieldID field(JNIEnv*, jclass, const char* name, const char* signature) {
    assert(std::strcmp(name, "INPUT_METHOD_SERVICE") == 0);
    assert(std::strcmp(signature, "Ljava/lang/String;") == 0);
    return ptr<jfieldID>(1);
}
jobject field_object(JNIEnv*, jclass, jfieldID) { return local(ptr<jobject>(kService)); }
jobject static_object(JNIEnv*, jclass, jmethodID m, va_list) {
    assert(reinterpret_cast<std::uintptr_t>(m) == Current);
    return local(ptr<jobject>(kThread));
}
jobject call_object(JNIEnv*, jobject object, jmethodID m, va_list args) {
    switch (reinterpret_cast<std::uintptr_t>(m)) {
    case Application: assert(value(object) == kThread); return local(ptr<jobject>(kContext));
    case SystemService:
        assert(value(object) == kContext);
        assert(value(va_arg(args, jobject)) == kService);
        return local(ptr<jobject>(kManager));
    case Enabled:
        assert(value(object) == kManager);
        ++state.manager_calls;
        return state.null_list ? nullptr : local(ptr<jobject>(kList));
    case Get: {
        assert(value(object) == kList);
        const int i = va_arg(args, int);
        assert(i >= 0 && i < static_cast<int>(state.ids.size()));
        return local(ptr<jobject>(100 + i));
    }
    case Id: {
        const int i = static_cast<int>(value(object)) - 100;
        if (i == state.fail_id) { state.exception = true; return nullptr; }
        return state.null_id.count(i) ? nullptr : local(ptr<jobject>(200 + i));
    }
    default: assert(false); return nullptr;
    }
}
jint call_int(JNIEnv*, jobject object, jmethodID m, va_list) {
    assert(value(object) == kList);
    assert(reinterpret_cast<std::uintptr_t>(m) == Size);
    ++state.size_calls;
    return static_cast<jint>(state.ids.size());
}
const char* utf(JNIEnv*, jstring string, jboolean* copy) {
    assert(copy == nullptr);
    const int i = static_cast<int>(value(string)) - 200;
    return state.null_chars.count(i) ? nullptr : state.ids.at(i).c_str();
}
void release(JNIEnv*, jstring, const char* chars) { assert(chars); ++state.release_count; }
void remove_local(JNIEnv*, jobject object) {
    assert(state.live.count(object) && state.live.at(object) > 0);
    if (--state.live[object] == 0) state.live.erase(object);
}
jboolean exception_check(JNIEnv*) { return state.exception ? JNI_TRUE : JNI_FALSE; }
}

static JNIEnv* vm_env = nullptr;
static jint get_env(JavaVM*, void** out, jint version) {
    assert(version == JNI_VERSION_1_6); *out=vm_env; return JNI_OK;
}
int main() {
    JNINativeInterface table{};
    table.FindClass = find_class;
    table.GetStaticMethodID = method;
    table.GetMethodID = method;
    table.GetStaticFieldID = field;
    table.GetStaticObjectField = field_object;
    table.CallStaticObjectMethodV = static_object;
    table.CallObjectMethodV = call_object;
    table.CallIntMethodV = call_int;
    table.GetStringUTFChars = utf;
    table.ReleaseStringUTFChars = release;
    table.DeleteLocalRef = remove_local;
    table.ExceptionCheck = exception_check;
    JNIEnv env{&table};
    vm_env=&env; JNIInvokeInterface vm_table{}; vm_table.GetEnv=get_env; JavaVM vm{&vm_table};

    auto result = enumerate_input_methods(&vm);
    assert(result.complete && !result.java_exception_pending);
    assert(result.service_names == state.ids); // preserves order and duplicates
    assert(state.manager_calls == 1 && state.size_calls == 1);
    assert(state.release_count == 3 && state.live.empty());

    state = State{}; state.null_list = true;
    result = enumerate_input_methods(&vm);
    assert(result.complete && result.service_names.empty() && state.size_calls == 0 && state.live.empty());

    state = State{}; state.ids.clear();
    result = enumerate_input_methods(&vm);
    assert(result.complete && result.service_names.empty() && state.size_calls == 1 && state.live.empty());

    state = State{}; state.null_id.insert(0); state.null_chars.insert(1);
    result = enumerate_input_methods(&vm);
    assert(result.complete && result.service_names == std::vector<std::string>({"", "", "fixture/.A"}));
    assert(state.release_count == 1 && state.live.empty());

    state = State{}; state.fail_id = 1;
    result = enumerate_input_methods(&vm);
    assert(!result.complete && result.java_exception_pending && state.exception);
    assert(result.service_names == std::vector<std::string>({"fixture/.A"}) && state.live.empty());
    assert(result.stage == "getServiceName result");

    state = State{}; state.exception = true;
    result = enumerate_input_methods(&vm);
    assert(!result.complete && result.java_exception_pending && state.find_calls == 0);

    state = State{};
    result = enumerate_input_methods(nullptr);
    assert(!result.complete && state.find_calls == 0);

    state = State{};
    result = enumerate_input_methods_from_context(&env, ptr<jobject>(kContext));
    assert(result.complete && result.service_names == state.ids && state.live.empty());
    assert(state.find_calls == 4); // borrowed Context was never deleted
    std::cout << "{\"result\":\"PASS\",\"scenarios\":8,\"scope\":\"JNI adapter mock signatures, list ordering, local refs, UTF release, pending exception\"}\n";
}
