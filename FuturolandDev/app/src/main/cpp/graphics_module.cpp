//
// Created by Lacko on 2018. 05. 07..
//
#include "vulkan_module.h"
#include "graphics_module.h"

#define DEBUG

PFN_draw draw_func=NULL;

VulkanModule *vkmodule=NULL;

GraphicsModule::GraphicsModule(ANativeWindow *wnd,uint32_t width,uint32_t height) {
    void *libvulkan=dlopen("libvulkan.so",RTLD_NOW|RTLD_LOCAL);
    if(libvulkan) {
        loadVulkan(libvulkan);
        vkmodule= new VulkanModule(wnd, width, height);
        if(!vkmodule->isSupported()){
#ifdef DEBUG
            __android_log_print(ANDROID_LOG_ERROR,"valmicsoda","Vulkan not supported");
#endif
        }else {
#ifdef DEBUG
            __android_log_print(ANDROID_LOG_ERROR,"valmicsoda","Vulkan supported");
#endif
            draw_func = VulkanModule::draw;

        }
    }
#ifdef DEBUG
    else{
        __android_log_print(ANDROID_LOG_ERROR,"valmicsoda","Vulkan absolutly not supported");
    }
#endif
    if(!draw_func){
        //TODO OpenGL Support
    }
}

PFN_draw GraphicsModule::getDrawFunc() {
    return draw_func;
}

GraphicsModule::~GraphicsModule() {
    delete vkmodule;
}
