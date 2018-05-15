//
// Created by Lacko on 2018. 05. 07..
//

#ifndef FUTUROLANDDEV_VULKAN_COMANDS_H
#define FUTUROLANDDEV_VULKAN_COMANDS_H

#include "vulkan_base.h"
#include "vulkan_render_surface.h"

class VulkanComands {
private:
    VulkanBase *base;
    VulkanRenderSurface *renderer;

    VkCommandPool pool;

    uint32_t img_count;

    void createCommandPool();
    VkCommandBuffer *allocateCmdBuffs();
public:
    void recordCommandBuffers(VkCommandBuffer *cmd_buff,vector<VulkanRenderCommand>);
    VulkanComands(VulkanBase* base,VulkanRenderSurface* renderer);
};


#endif //FUTUROLANDDEV_VULKAN_COMANDS_H
