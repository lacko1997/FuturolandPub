//
// Created by Lacko on 2018. 05. 07..
//

#ifndef FUTUROLANDDEV_VULKAN_MODULE_H
#define FUTUROLANDDEV_VULKAN_MODULE_H


#include "vulkan_base.h"
#include "vulkan_render_surface.h"
#include "graphics_module.h"

class VulkanModule {
private:
    VulkanBase *base;
    VulkanRenderSurface *surface;
    void draw();
public:

    PFN_draw getDrawFunc(){return draw;};
    bool isSupported(){};
    VulkanModule();
};


#endif //FUTUROLANDDEV_VULKAN_MODULE_H
