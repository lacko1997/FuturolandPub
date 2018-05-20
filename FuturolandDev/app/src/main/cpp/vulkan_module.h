#ifndef FUTUROLANDDEV_VULKAN_MODULE_H
#define FUTUROLANDDEV_VULKAN_MODULE_H

#include "vulkan_base.h"
#include "vulkan_render_surface.h"
#include "graphics_module.h"
#include "vulkan_commands.h"

class VulkanModule {
private:
    VulkanBase *base;
    VulkanRenderSurface *surface;
    VulkanCommands *commander;
public:
    static void draw();
    bool isSupported(){return base->isSupported();};
    VulkanModule(ANativeWindow *wnd,uint32_t width,uint32_t height);
    ~VulkanModule();
};
#endif //FUTUROLANDDEV_VULKAN_MODULE_H
