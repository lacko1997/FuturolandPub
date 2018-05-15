#include <jni.h>
#include <string>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <dlfcn.h>

using namespace std;
string messages;

ANativeWindow *wnd;

extern "C" JNIEXPORT void JNICALL Java_xyz_productions_phenyl_futuroland_futuroland_Renderer_initRenderer(JNIEnv *env, jobject instance, jobject surface) {
    wnd=ANativeWindow_fromSurface(env,surface);

    void *libvulkan=dlopen("libvulkan.so",RTLD_NOW|RTLD_LOCAL);
}

extern "C" JNIEXPORT jstring JNICALL Java_xyz_productions_phenyl_futuroland_futuroland_Renderer_reciveMessage(JNIEnv *env, jobject instance) {
    return env->NewStringUTF(messages.c_str());
}