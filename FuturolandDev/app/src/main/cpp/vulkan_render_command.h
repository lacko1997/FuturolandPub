#ifndef FUTUROLANDDEV_VULKAN_RENDER_COMMAND_H
#define FUTUROLANDDEV_VULKAN_RENDER_COMMAND_H

#include "vulkan_func.h"
#include "graphics_module.h"

class VulkanRenderCommand {
public:
    virtual void cmd(VkCommandBuffer cmd_buff)=0;
    VulkanRenderCommand(){}
};


#endif //FUTUROLANDDEV_VULKAN_RENDER_COMMAND_H
