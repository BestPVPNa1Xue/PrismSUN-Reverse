#include "../include/xposed.hpp"
#include <algorithm>

namespace prism_old {
namespace {
template<class T> struct Ref {
 JNIEnv* e;T p;
 Ref(JNIEnv* env,T value):e(env),p(value){}
 ~Ref(){if(p)e->DeleteLocalRef(p);}
 Ref(const Ref&)=delete;Ref& operator=(const Ref&)=delete;
 operator T()const{return p;}
};
bool clear_exception(JNIEnv* e) { if(!e->ExceptionCheck())return false;e->ExceptionClear();return true; }
std::string utf(JNIEnv* e,jstring s) {
 if(!s)return {};
 const char* p=e->GetStringUTFChars(s,nullptr);if(!p)return {};
 std::string out(p);e->ReleaseStringUTFChars(s,p);return out;
}
}
jclass find_loaded(JNIEnv* e,jobject loader,const char* name) {
 Ref<jclass> c(e,e->FindClass("java/lang/VMClassLoader"));
 if(clear_exception(e)||!c.p)return nullptr;
 auto m=e->GetStaticMethodID(c,"findLoadedClass","(Ljava/lang/ClassLoader;Ljava/lang/String;)Ljava/lang/Class;");
 if(clear_exception(e)||!m)return nullptr;
 Ref<jstring> s(e,e->NewStringUTF(name));
 if(!s.p)return nullptr;
 auto found=static_cast<jclass>(e->CallStaticObjectMethod(c,m,loader,s.p));
 if(clear_exception(e)) { if(found)e->DeleteLocalRef(found);return nullptr; }
 return found;
}
bool set_disable_hooks(JNIEnv* e,jclass c) {
 auto f=e->GetStaticFieldID(c,"disableHooks","Z");
 clear_exception(e);if(!f)return false;
 e->SetStaticBooleanField(c,f,JNI_TRUE);return !clear_exception(e);
}
std::string field_name_by_type(JNIEnv* e,jclass c,int static_bit,jclass type) {
 Ref<jclass> cls(e,e->FindClass("java/lang/Class"));
 Ref<jclass> fld(e,e->FindClass("java/lang/reflect/Field"));
 if(!cls.p||!fld.p)return {};
 auto declared=e->GetMethodID(cls,"getDeclaredFields","()[Ljava/lang/reflect/Field;");
 auto modifiers=e->GetMethodID(fld,"getModifiers","()I");
 auto get_type=e->GetMethodID(fld,"getType","()Ljava/lang/Class;");
 auto name=e->GetMethodID(fld,"getName","()Ljava/lang/String;");
 if(!declared||!modifiers||!get_type||!name)return {};
 Ref<jobjectArray> fields(e,static_cast<jobjectArray>(e->CallObjectMethod(c,declared)));
 if(!fields.p)return {};
 for(jsize i=0;i<e->GetArrayLength(fields);++i) {
  Ref<jobject> f(e,e->GetObjectArrayElement(fields,i));
  if((e->CallIntMethod(f,modifiers)&8)!=static_bit)continue;
  Ref<jobject> t(e,e->CallObjectMethod(f,get_type));
  if(!e->IsSameObject(type,t))continue;
  Ref<jstring> n(e,static_cast<jstring>(e->CallObjectMethod(f,name)));return utf(e,n);
 }
 return {};
}
std::string epic_owner(JNIEnv* e,jclass c) {
 Ref<jclass> cls(e,e->FindClass("java/lang/Class"));
 Ref<jclass> met(e,e->FindClass("java/lang/reflect/Method"));
 Ref<jclass> str(e,e->FindClass("java/lang/String"));
 if(!cls.p||!met.p||!str.p)return {};
 auto declared=e->GetMethodID(cls,"getDeclaredMethods","()[Ljava/lang/reflect/Method;");
 auto mods=e->GetMethodID(met,"getModifiers","()I");
 auto params=e->GetMethodID(met,"getParameterTypes","()[Ljava/lang/Class;");
 auto type=e->GetMethodID(met,"getReturnType","()Ljava/lang/Class;");
 auto name=e->GetMethodID(met,"getName","()Ljava/lang/String;");
 if(!declared||!mods||!params||!type||!name)return {};
 Ref<jobjectArray> methods(e,static_cast<jobjectArray>(e->CallObjectMethod(c,declared)));
 if(!methods.p)return {};
 for(jsize i=0;i<e->GetArrayLength(methods);++i) {
  Ref<jobject> m(e,e->GetObjectArrayElement(methods,i));
  if((e->CallIntMethod(m,mods)&0x108)!=8)continue;
  Ref<jobjectArray> p(e,static_cast<jobjectArray>(e->CallObjectMethod(m,params)));
  if(!p.p||e->GetArrayLength(p)!=0)continue;
  Ref<jobject> t(e,e->CallObjectMethod(m,type));if(!e->IsSameObject(str,t))continue;
  Ref<jstring> n(e,static_cast<jstring>(e->CallObjectMethod(m,name)));
  auto mid=e->GetStaticMethodID(c,utf(e,n).c_str(),"()Ljava/lang/String;");
  if(!mid){clear_exception(e);continue;}
  Ref<jstring> value(e,static_cast<jstring>(e->CallStaticObjectMethod(c,mid)));
  if(clear_exception(e)||!value.p)continue;
  auto out=utf(e,value);if(!out.empty()&&out.front()=='L')out.erase(0,1);
  if(auto end=out.find(';');end!=out.npos)out.resize(end);
  return out;
 }
 return {};
}
bool clear_callbacks(JNIEnv* e,jclass bridge) {
 auto f=e->GetStaticFieldID(bridge,"sHookedMethodCallbacks","Ljava/util/Map;");
 clear_exception(e);
 if(!f) {
  Ref<jclass> type(e,e->FindClass("java/util/Map"));
  auto name=field_name_by_type(e,bridge,8,type);
  if(name.empty())return false;
  f=e->GetStaticFieldID(bridge,name.c_str(),"Ljava/util/Map;");
 }
 if(!f)return false;
 Ref<jobject> map(e,e->GetStaticObjectField(bridge,f));
 Ref<jclass> hash(e,e->FindClass("java/util/HashMap"));
 if(!map.p||!hash.p||!e->IsInstanceOf(map,hash))return false;
 auto empty=e->GetMethodID(hash,"isEmpty","()Z");
 if(!empty)return false;
 jboolean flag=e->CallBooleanMethod(map,empty);
 if(flag) { Ref<jclass> actual(e,e->GetObjectClass(map));flag=e->CallNonvirtualBooleanMethod(map,actual,empty); }
 auto values=e->GetMethodID(hash,"values","()Ljava/util/Collection;");
 if(!values)return false;
 jobject collection;
 if(flag==JNI_TRUE)collection=e->CallObjectMethod(map,values);
 else { Ref<jclass> actual(e,e->GetObjectClass(map));collection=e->CallNonvirtualObjectMethod(map,actual,values); }
 Ref<jobject> coll(e,collection);
 Ref<jclass> cc(e,e->FindClass("java/util/Collection"));
 if(!coll.p||!cc.p)return false;
 auto iterator=e->GetMethodID(cc,"iterator","()Ljava/util/Iterator;");if(!iterator)return false;
 Ref<jobject> it(e,e->CallObjectMethod(coll,iterator));
 Ref<jclass> ic(e,e->FindClass("java/util/Iterator"));if(!it.p||!ic.p)return false;
 auto has_next=e->GetMethodID(ic,"hasNext","()Z");
 auto next=e->GetMethodID(ic,"next","()Ljava/lang/Object;");
 Ref<jclass> object(e,e->FindClass("java/lang/Object"));
 if(!has_next||!next||!object.p)return false;
 Ref<jobjectArray> zero(e,e->NewObjectArray(0,object,nullptr));
 if(!zero.p)return false;
 jfieldID array_field=nullptr;bool success=false;
 while(e->CallBooleanMethod(it,has_next)) {
  Ref<jobject> value(e,e->CallObjectMethod(it,next));if(!value.p)continue;
  if(!array_field) {
   Ref<jclass> actual(e,e->GetObjectClass(value));
   Ref<jclass> type(e,e->FindClass("[Ljava/lang/Object;"));
   auto name=field_name_by_type(e,actual,0,type);if(name.empty())break;
   array_field=e->GetFieldID(actual,name.c_str(),"[Ljava/lang/Object;");
   if(!array_field)break;
  }
  e->SetObjectField(value,array_field,zero);
  if(!clear_exception(e))success=true;
 }
 return success;
}
bool clear_epic_family(JNIEnv* e,jobject loader) {
 Ref<jclass> native(e,find_loaded(e,loader,"me/weishu/epic/art2/EpicNative"));
 if(native.p) {
  const auto name=epic_owner(e,native);
  if(!name.empty()) { Ref<jclass> c(e,find_loaded(e,loader,name.c_str()));if(c.p&&clear_callbacks(e,c))return true; }
 }
 for(const char* name:{"me/weishu/epic/art2/EpicBridge","de/robv/android/xposed/DexposedBridge","de/robv/android/xposed/XposedBridge"}) {
  Ref<jclass> c(e,find_loaded(e,loader,name));if(c.p&&clear_callbacks(e,c))return true;
 }
 return false;
}
void inspect_loader(JNIEnv* e,jobject loader,XposedState& state) {
 Ref<jclass> c(e,find_loaded(e,loader,"de/robv/android/xposed/XposedBridge"));
 if(!c.p)return;
 if(state.value==0)state.value=1;
 set_disable_hooks(e,c);
 if(clear_epic_family(e,loader)&&state.value<2)state.value=2;
}
void inspect_stack(JNIEnv* e,XposedState& state) {
 if(state.value)return;
 Ref<jclass> thread(e,e->FindClass("java/lang/Thread"));if(!thread.p)return;
 auto current=e->GetStaticMethodID(thread,"currentThread","()Ljava/lang/Thread;");
 auto trace=e->GetMethodID(thread,"getStackTrace","()[Ljava/lang/StackTraceElement;");
 Ref<jclass> elem(e,e->FindClass("java/lang/StackTraceElement"));if(!current||!trace||!elem.p)return;
 auto name=e->GetMethodID(elem,"getClassName","()Ljava/lang/String;");if(!name)return;
 Ref<jobject> self(e,e->CallStaticObjectMethod(thread,current));if(!self.p)return;
 Ref<jobjectArray> frames(e,static_cast<jobjectArray>(e->CallObjectMethod(self,trace)));if(!frames.p)return;
 const std::string prefix="de.robv.android.xposed.XC_MethodHook";
 for(jsize i=0;i<e->GetArrayLength(frames);++i) {
  Ref<jobject> f(e,e->GetObjectArrayElement(frames,i));
  Ref<jstring> n(e,static_cast<jstring>(e->CallObjectMethod(f,name)));
  if(utf(e,n).compare(0,prefix.size(),prefix)==0) { state.value=3;break; }
 }
}
bool accept_token(XposedState& s,std::uintptr_t token) {
 if(!token){const bool had=!s.visited.empty();s.visited.clear();return had;}
 if(std::find(s.visited.begin(),s.visited.end(),token)!=s.visited.end())return false;
 s.visited.push_back(token);return true;
}
}
