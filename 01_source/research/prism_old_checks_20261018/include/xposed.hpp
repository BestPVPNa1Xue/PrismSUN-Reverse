#pragma once
#include <jni.h>
#include <cstdint>
#include <string>
#include <vector>

namespace prism_old {
// Persistent 0x654a08: 0=none, 1=bridge, 2=callback write, 3=stack fallback.
struct XposedState { unsigned value=0;std::vector<std::uintptr_t> visited; };
jclass find_loaded(JNIEnv*,jobject loader,const char* name);
bool set_disable_hooks(JNIEnv*,jclass);
std::string field_name_by_type(JNIEnv*,jclass,int static_bit,jclass type);
std::string epic_owner(JNIEnv*,jclass epic_native);
bool clear_callbacks(JNIEnv*,jclass bridge);
bool clear_epic_family(JNIEnv*,jobject loader);
void inspect_loader(JNIEnv*,jobject loader,XposedState&);
void inspect_stack(JNIEnv*,XposedState&);
// Caller supplies ART-discovered loader/token pairs; token zero clears this scan cache.
bool accept_token(XposedState&,std::uintptr_t token);
}
