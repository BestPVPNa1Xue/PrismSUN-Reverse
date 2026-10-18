#include "../include/xposed.hpp"
#include <cassert>
#include <cstdarg>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <vector>
using namespace prism_old;
namespace {
struct Object {std::string kind,name,sig,type;int flags=0;std::vector<jobject> items;};
std::vector<std::unique_ptr<Object>> objects;
std::map<std::string,jclass> classes;
std::set<std::string> loaded;
bool map_exists=true,hashmap=true,virtual_empty=false,nonvirtual_empty=false;
bool field_missing=false,write_error=false,pending=false;
int writes=0,disabled=0,nonvirtual_values=0,virtual_values=0;
std::size_t index=0; jobject map_obj,collection,iterator,callbacks;
std::vector<std::string> stack_names;
Object& get(const void* p){return *reinterpret_cast<Object*>(const_cast<void*>(p));}
jobject object(const std::string& kind,const std::string& name="") {
 auto p=std::make_unique<Object>();p->kind=kind;p->name=name;
 auto out=reinterpret_cast<jobject>(p.get());objects.push_back(std::move(p));return out;
}
jclass klass(JNIEnv*,const char* n) {
 auto it=classes.find(n);if(it!=classes.end())return it->second;
 auto out=reinterpret_cast<jclass>(object("class",n));classes[n]=out;return out;
}
jmethodID method(JNIEnv*,jclass,const char* name,const char* sig) {
 auto out=object("method",name);get(out).sig=sig;return reinterpret_cast<jmethodID>(out);
}
jfieldID field(JNIEnv*,jclass,const char* name,const char* sig) {
 if(field_missing && std::string(name)=="sHookedMethodCallbacks"){pending=true;return nullptr;}
 auto out=object("fieldID",name);get(out).sig=sig;return reinterpret_cast<jfieldID>(out);
}
jstring new_string(JNIEnv*,const char* s){return reinterpret_cast<jstring>(object("string",s));}
const char* utf(JNIEnv*,jstring s,jboolean*){return get(s).name.c_str();}
void release(JNIEnv*,jstring,const char*){}
void drop(JNIEnv*,jobject){}
jboolean exception(JNIEnv*){return pending;}
void clear(JNIEnv*){pending=false;}
jobject array(std::vector<jobject> items){auto a=object("array");get(a).items=std::move(items);return a;}
jsize length(JNIEnv*,jarray a){return static_cast<jsize>(get(a).items.size());}
jobject item(JNIEnv*,jobjectArray a,jsize i){return get(a).items.at(static_cast<unsigned>(i));}
jobject call(JNIEnv* e,jobject o,jmethodID m,va_list) {
 const auto& n=get(m).name;
 if(n=="values"){++virtual_values;return collection;}
 if(n=="iterator")return iterator;
 if(n=="next")return get(callbacks).items.at(index++);
 if(n=="getDeclaredFields" || n=="getDeclaredMethods")return array(get(o).items);
 if(n=="getType" || n=="getReturnType")return klass(e,get(o).type.c_str());
 if(n=="getParameterTypes")return array(get(o).items);
 if(n=="getName" || n=="getClassName")return new_string(e,get(o).name.c_str());
 if(n=="getStackTrace"){std::vector<jobject> v;for(auto& s:stack_names)v.push_back(object("frame",s));return array(v);}
 assert(false);return nullptr;
}
jobject nonvirtual(JNIEnv* e,jobject o,jclass,jmethodID m,va_list v){++nonvirtual_values;--virtual_values;return call(e,o,m,v);}
jobject statik(JNIEnv* e,jclass,jmethodID m,va_list args) {
 const auto& n=get(m).name;
 if(n=="currentThread")return object("thread");
 if(n=="findLoadedClass") {
  (void)va_arg(args,jobject);auto s=va_arg(args,jstring);auto name=get(s).name;
  return loaded.count(name)?klass(e,name.c_str()):nullptr;
 }
 return new_string(e,"Lexample/Owner;");
}
jint integer(JNIEnv*,jobject o,jmethodID,va_list){return get(o).flags;}
jboolean boolean(JNIEnv*,jobject,jmethodID m,va_list) {
 return get(m).name=="isEmpty"?virtual_empty:index<get(callbacks).items.size();
}
jboolean nonvirtual_boolean(JNIEnv*,jobject,jclass,jmethodID,va_list){return nonvirtual_empty;}
jboolean same(JNIEnv*,jobject a,jobject b){return a==b;}
jboolean instance(JNIEnv*,jobject,jclass){return hashmap;}
jclass object_class(JNIEnv* e,jobject o){return klass(e,get(o).type.empty()?"Value":get(o).type.c_str());}
jobject static_field(JNIEnv*,jclass,jfieldID){return map_exists?map_obj:nullptr;}
void set_boolean(JNIEnv*,jclass,jfieldID,jboolean v){assert(v==1);++disabled;}
jobjectArray new_array(JNIEnv*,jsize n,jclass,jobject){assert(n==0);return reinterpret_cast<jobjectArray>(array({}));}
void set_object(JNIEnv*,jobject,jfieldID f,jobject value){assert(get(f).sig=="[Ljava/lang/Object;");assert(get(value).items.empty());++writes;pending=write_error;}
void setup(JNIEnv* e) {
 objects.clear();classes.clear();loaded.clear();stack_names.clear();
 map_exists=hashmap=true;virtual_empty=nonvirtual_empty=field_missing=write_error=pending=false;
 writes=disabled=nonvirtual_values=virtual_values=0;index=0;
 map_obj=object("map");collection=object("collection");iterator=object("iterator");
 callbacks=array({object("callback"),object("callback")});
 auto f=object("field","elements");get(f).type="[Ljava/lang/Object;";
 get(klass(e,"Value")).items={f};
 auto b=klass(e,"de/robv/android/xposed/XposedBridge");
 auto mf=object("field","renamedCallbacks");get(mf).flags=8;get(mf).type="java/util/Map";get(b).items={mf};
}
}
int main(){
 JNINativeInterface table{};JNIEnv e{&table};
 table.FindClass=klass;table.GetMethodID=method;table.GetStaticMethodID=method;
 table.GetFieldID=field;table.GetStaticFieldID=field;
 table.NewStringUTF=new_string;table.GetStringUTFChars=utf;table.ReleaseStringUTFChars=release;
 table.DeleteLocalRef=drop;table.ExceptionCheck=exception;table.ExceptionClear=clear;
 table.GetArrayLength=length;table.GetObjectArrayElement=item;
 table.CallObjectMethodV=call;table.CallNonvirtualObjectMethodV=nonvirtual;table.CallStaticObjectMethodV=statik;
 table.CallIntMethodV=integer;table.CallBooleanMethodV=boolean;table.CallNonvirtualBooleanMethodV=nonvirtual_boolean;
 table.IsSameObject=same;table.IsInstanceOf=instance;table.GetObjectClass=object_class;
 table.GetStaticObjectField=static_field;table.SetStaticBooleanField=set_boolean;
 table.NewObjectArray=new_array;table.SetObjectField=set_object;
 unsigned cases=0;
 for(int mode=0;mode<6;++mode){setup(&e);auto bridge=klass(&e,"de/robv/android/xposed/XposedBridge");
  if(mode==1)field_missing=true;
  if(mode==2)hashmap=false;
  if(mode==3)write_error=true;
  if(mode==4){virtual_empty=true;nonvirtual_empty=true;}
  if(mode==5){get(callbacks).items.clear();}
  bool result=clear_callbacks(&e,bridge);
  assert(result==(mode==0||mode==1||mode==4));
  if(mode==4)assert(virtual_values==1 && nonvirtual_values==0);
  if(mode==0)assert(nonvirtual_values==1 && virtual_values==0 && writes==2);
  ++cases;
 }
 for(int mode=0;mode<3;++mode){setup(&e);XposedState s;
  if(mode)loaded.insert("de/robv/android/xposed/XposedBridge");
  if(mode==1)map_exists=false;
  inspect_loader(&e,nullptr,s);assert(s.value==static_cast<unsigned>(mode));
  assert(disabled==(mode?1:0));++cases;
 }
 setup(&e);XposedState s;stack_names={"normal.Frame","de.robv.android.xposed.XC_MethodHookSuffix"};
 inspect_stack(&e,s);assert(s.value==3);++cases;
 assert(accept_token(s,42));assert(!accept_token(s,42));++cases;
 setup(&e);auto native=klass(&e,"EpicNative");auto m=object("method","owner");get(m).type="java/lang/String";get(m).flags=8;
 get(native).items={m};assert(epic_owner(&e,native)=="example/Owner");++cases;
 std::cout<<"{\"jni_scenarios\":"<<cases<<",\"result\":\"PASS\"}\n";
}

