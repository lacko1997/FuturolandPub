#include <jni.h>
#include <string>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include "vulkan_func.h"
#include "graphics_module.h"
#include <android/log.h>
#include <pthread.h>

#define DEBUG

using namespace std;
string vk_messages;

ANativeWindow *wnd;

pthread_t render_thread;
pthread_mutex_t mutex;

PFN_draw draw;

bool running=true;

void* gameLoop(void*){
    while(running){
        draw();
    }
    return NULL;
}
GraphicsModule *gmodule=NULL;

extern "C" JNIEXPORT void JNICALL Java_xyz_productions_phenyl_futuroland_futuroland_Renderer_initRenderer(JNIEnv *env, jobject instance, jobject surface) {
    wnd=ANativeWindow_fromSurface(env,surface);
    if(wnd) {
        int width = ANativeWindow_getWidth(wnd);
        int height = ANativeWindow_getHeight(wnd);
#ifdef DEBUG
        __android_log_print(ANDROID_LOG_ERROR,"valami","%d %d",width,height);
#endif
        gmodule=new GraphicsModule(wnd, (uint32_t) width, (uint32_t) height);
        draw=gmodule->getDrawFunc();
        pthread_create(&render_thread,NULL,gameLoop,NULL);
        pthread_mutex_init(&mutex,NULL);
    }
#ifdef DEBUG
    else {
        __android_log_print(ANDROID_LOG_ERROR, "error", "native window not found");
    }
#endif
}

extern "C" JNIEXPORT jstring JNICALL Java_xyz_productions_phenyl_futuroland_futuroland_Renderer_reciveMessage(JNIEnv *env, jobject instance) {
    return env->NewStringUTF(vk_messages.c_str());
}
extern "C" JNIEXPORT void JNICALL Java_xyz_productions_phenyl_futuroland_futuroland_MainActivity_start(JNIEnv *env, jobject instance) {
    running=true;
    if(gmodule!=NULL) {
        pthread_create(&render_thread, NULL, gameLoop, NULL);
    }
}
extern "C" JNIEXPORT void JNICALL Java_xyz_productions_phenyl_futuroland_futuroland_MainActivity_pause(JNIEnv *env, jobject instance) {
    void *value;
    running=false;
    pthread_join(render_thread,&value);
}