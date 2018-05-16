#include <jni.h>
#include <string>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include "vulkan_func.h"
#include "graphics_module.h"
#include <android/log.h>

#define DEBUG

using namespace std;
string vk_messages;

ANativeWindow *wnd;

extern "C" JNIEXPORT void JNICALL Java_xyz_productions_phenyl_futuroland_futuroland_Renderer_initRenderer(JNIEnv *env, jobject instance, jobject surface) {
    wnd=ANativeWindow_fromSurface(env,surface);
    if(wnd) {
        int width = ANativeWindow_getWidth(wnd);
        int height = ANativeWindow_getHeight(wnd);
#ifdef DEBUG
        __android_log_print(ANDROID_LOG_ERROR,"valami","%d %d",width,height);
#endif
        GraphicsModule module = GraphicsModule(wnd, (uint32_t) width, (uint32_t) height);
    }else{
#ifdef DEBUG
        __android_log_print(ANDROID_LOG_ERROR,"error","native window not found");
#endif
    }
}

extern "C" JNIEXPORT jstring JNICALL Java_xyz_productions_phenyl_futuroland_futuroland_Renderer_reciveMessage(JNIEnv *env, jobject instance) {
    return env->NewStringUTF(vk_messages.c_str());
}
