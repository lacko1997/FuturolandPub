#include <jni.h>
#include <string>
#include <android/log.h>
#include <pthread.h>

#include "vulkan_func.h"
#include "graphics_module.h"


#define DEBUG

using namespace std;
string vk_messages;

ANativeWindow *wnd;

pthread_t render_thread;
pthread_mutex_t p_mutex;

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
        running=true;
        pthread_create(&render_thread,NULL,gameLoop,NULL);
        pthread_mutex_init(&p_mutex,NULL);
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
    if(!running&&gmodule!=NULL) {
        pthread_create(&render_thread, NULL, gameLoop, NULL);
    }
}
extern "C" JNIEXPORT void JNICALL Java_xyz_productions_phenyl_futuroland_futuroland_MainActivity_pause(JNIEnv *env, jobject instance) {
    if(running) {
        void *value;
        running = false;
        pthread_join(render_thread, &value);
    }
}
extern "C" JNIEXPORT void JNICALL Java_xyz_productions_phenyl_futuroland_futuroland_MainActivity_stop(JNIEnv *env, jobject instance) {
    if(running) {
        void *value;
        running = false;
        pthread_join(render_thread, &value);
    }

    delete gmodule;
    pthread_mutex_destroy(&p_mutex);
}
extern "C" JNIEXPORT void JNICALL Java_xyz_productions_phenyl_futuroland_futuroland_Resources_Model3D_modelData(JNIEnv *env,
                                                                              jobject instance,
                                                                              jfloatArray data_,
                                                                              jshortArray index_data_) {
    jfloat *data = env->GetFloatArrayElements(data_, NULL);
    jshort *index_data = env->GetShortArrayElements(index_data_, NULL);

    jsize data_length=env->GetArrayLength(data_);
    jsize index_data_length=env->GetArrayLength(index_data_);

    Model3D model={};
    model.vertex_data= (float *) malloc(sizeof(float) * data_length);
    model.index_data= (short *) malloc(sizeof(short) * index_data_length);

    env->ReleaseFloatArrayElements(data_, data, 0);
    env->ReleaseShortArrayElements(index_data_, index_data, 0);
}