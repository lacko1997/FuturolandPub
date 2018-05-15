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
    VulkanDefferedComponent *deffered;

    VkFramebuffer *fbos;
    VkRenderPass renderpass;

    uint32_t depens_count;
    VkSubpassDependency *depens;
    uint32_t subpass_count;
    VkSubpassDescription *subpasses;

    uint32_t attachment_count;
    VkAttachmentDescription *attachments;

    void depthPeeling();

    void deferedRendering();

    void singleSubpass();
    void singleDependency();
    void singleAttachments();

    void createRenderpass();
    void subpassDependency();
    void createFrameBuffers();
public:
    VkRenderPass getRenderpass(){return renderpass;}
    VkFramebuffer *getFramebuffers(uint32_t *img_count){
        base->getImages(img_count);
        return fbos;
    }
    VulkanRenderSurface();
};


#endif //FUTUROLANDDEV_VULKAN_RENDERER_H
