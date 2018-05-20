//
// Created by Lacko on 2018. 05. 07..
//

#ifndef FUTUROLANDDEV_VULKAN_RENDERER_H
#define FUTUROLANDDEV_VULKAN_RENDERER_H

#include "vulkan_base.h"
#include "vulkan_deffered_component.h"

class VulkanRenderSurface {
private:
    VulkanBase *base;
    VkRenderPass renderpass;
    VkFramebuffer* fbos;
    uint32_t img_count;

    void createRenderpass();
    void createFrameBuffers();
public:
    VkRenderPass getRenderpass(){return renderpass;}
    VkFramebuffer *getFramebuffers(){return fbos;}
    uint32_t getImgCount(){return img_count;};
    VulkanRenderSurface(VulkanBase *base);
    ~VulkanRenderSurface();
};


#endif //FUTUROLANDDEV_VULKAN_RENDERER_H
