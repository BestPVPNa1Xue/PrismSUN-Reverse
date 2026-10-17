#include <cstddef>
#include <jni.h>

static_assert(sizeof(void*) == 8);
static_assert(offsetof(JNINativeInterface, FindClass) == 0x30);
static_assert(offsetof(JNINativeInterface, ExceptionCheck) == 1824);
static_assert(offsetof(JNINativeInterface, ExceptionClear) == 136);
static_assert(offsetof(JNINativeInterface, DeleteLocalRef) == 184);
