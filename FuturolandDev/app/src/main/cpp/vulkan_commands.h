#ifndef FUTUROLANDDEV_VULKAN_COMANDS_H
#define FUTUROLANDDEV_VULKAN_COMANDS_H

#include "vulkan_base.h"
#include "vulkan_render_surface.h"

class VulkanCommands {
private:
    VulkanBase *base;
    VulkanRenderSurface *renderer;

    VkCommandPool pool;
    VkCommandBuffer *cmd_buffs;

    uint32_t img_count;

    void createCommandPool();
    VkCommandBuffer *allocateCmdBuffs();
public:
    VkCommandBuffer *getCmdBuffs(){return cmd_buffs;}
    void recordCommandBuffers(VkCommandBuffer *cmd_buff);
    VulkanCommands(VulkanBase* base,VulkanRenderSurface* renderer);
};


#endif //FUTUROLANDDEV_VULKAN_COMANDS_H
