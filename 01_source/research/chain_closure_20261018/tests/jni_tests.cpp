#include "../src/classes_jni.hpp"
#include <cstddef>
#include <iostream>
#include <stdexcept>

using namespace prism::chains;
static_assert(offsetof(JNINativeInterface, FindClass)==0x30);
static_assert(offsetof(JNINativeInterface, ExceptionCheck)==0x720);
static_assert(offsetof(JNINativeInterface, ExceptionClear)==0x88);
static_assert(offsetof(JNINativeInterface, DeleteLocalRef)==0xb8);
namespace {
int checks=0;
void check(bool x,const char* name) {++checks;if(!x)throw std::runtime_error(name);}
struct State {
    jint get_result=JNI_OK, attach_result=JNI_OK;
    int gets=0,attaches=0,detaches=0,finds=0,clears=0,deletes=0;
    bool exception=false;
    std::vector<std::string> names;
} s;
JNIEnv* fake_env=nullptr;
jint get(JavaVM*,void** out,jint version) {
    if(version!=JNI_VERSION_1_6)return JNI_EVERSION;
    ++s.gets;*out=s.get_result==JNI_OK?fake_env:nullptr;return s.get_result;
}
jint attach(JavaVM*,JNIEnv** out,void* args) {
    if(args)return JNI_ERR;
    ++s.attaches;*out=s.attach_result==JNI_OK?fake_env:nullptr;return s.attach_result;
}
jint detach(JavaVM*) {++s.detaches;return JNI_OK;}
jclass find(JNIEnv*,const char* name) {
    ++s.finds;s.names.emplace_back(name);
    if(s.names.back()=="bad") {s.exception=true;return nullptr;}
    if(s.names.back()=="null")return nullptr;
    return reinterpret_cast<jclass>(std::uintptr_t{1});
}
jboolean pending(JNIEnv*) {return s.exception?JNI_TRUE:JNI_FALSE;}
void clear(JNIEnv*) {++s.clears;s.exception=false;}
void remove(JNIEnv*,jobject ref) {if(ref)++s.deletes;}
JsonValue value(const char* name) {return {16,0,std::string(name),{}};}
}
int main() {
    try {
        JNINativeInterface table{};table.FindClass=find;table.ExceptionCheck=pending;
        table.ExceptionClear=clear;table.DeleteLocalRef=remove;
        JNIEnv env{&table};fake_env=&env;
        JNIInvokeInterface vt{};vt.GetEnv=get;vt.AttachCurrentThread=attach;vt.DetachCurrentThread=detach;
        JavaVM vm{&vt};JsonValue config{32,0,{}, {value("ok"),value("bad"),value("null"),value("ok")}};
        auto r=probe_classes_jni(&config,&vm);
        check(r.event==22 && r.visible==std::vector<std::string>{"ok","ok"},"JNI class results");
        check(s.gets==1 && !s.attaches && !s.detaches,"already attached thread ownership");
        check(s.finds==4 && s.clears==1 && s.deletes==2 && !s.exception,"JNI refs/exceptions");
        s={};s.get_result=JNI_EDETACHED;r=probe_classes_jni(&config,&vm);
        check(r.event==22 && s.attaches==1 && s.detaches==1,"native thread attach/detach");
        s={};s.get_result=JNI_EDETACHED;s.attach_result=JNI_ERR;r=probe_classes_jni(&config,&vm);
        check(!r.event && r.diagnostic==0xbba && s.attaches==1 && !s.detaches && !s.finds,"failed attach no detach");
        s={};s.get_result=JNI_EVERSION;r=probe_classes_jni(&config,&vm);
        check(!r.event && !s.attaches && !s.finds,"version failure not attached");
        s={};r=probe_classes_jni(&config,nullptr);
        check(!r.event && r.diagnostic==0xbba && !s.gets,"null VM error");
        s={};r=probe_classes_jni(nullptr,&vm);
        check(r.event==22 && !s.gets,"disabled skips GetEnv");
        s={};config.children={value("ok"),{8,0,{},{}},value("later")};r=probe_classes_jni(&config,&vm);
        check(r.stopped_at_non_string && s.finds==1,"typed config stop through JNI");
        s={};s.get_result=JNI_EDETACHED;config.children={{16,0,{}, {}}};r=probe_classes_jni(&config,&vm);
        check(!r.complete && s.detaches==1,"null valuestring still detaches");
        std::cout<<"{\"suite\":\"class-JNI-adapter\",\"checks\":"<<checks<<",\"passed\":true,\"runtime\":\"host JNI/VM function table mock\"}\n";
    } catch(const std::exception& e) {std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}
}
