//
// Created by Lacko on 2018. 05. 07..
//

#include "vulkan_render_surface.h"

void VulkanRenderSurface::createRenderpass() {
    VkRenderPassCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    info.flags=0;
    info.pNext=NULL;
    info.subpassCount=subpass_count;
    info.pSubpasses=subpasses;
    info.dependencyCount=depens_count;
    info.pDependencies=depens;
    info.attachmentCount=attachment_count;
    info.pAttachments=attachments;

    pfn_vkCreateRenderPass(base->getDevice(),&info,NULL,&renderpass);
}

void VulkanRenderSurface::singleSubpass() {
    subpass_count=1;

    subpasses=(VkSubpassDescription*)malloc(sizeof(VkSubpassDescription)*subpass_count);

    VkAttachmentReference depth_ref={};
    depth_ref.layout=VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    depth_ref.attachment=1;

    VkAttachmentReference color_ref={};
    color_ref.layout=VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    color_ref.attachment=0;

    subpasses[0].flags=0;
    subpasses[0].inputAttachmentCount=0;
    subpasses[0].pInputAttachments=NULL;
    subpasses[0].pipelineBindPoint=VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpasses[0].preserveAttachmentCount=1;
    subpasses[0].pPreserveAttachments=NULL;
    subpasses[0].pDepthStencilAttachment=&depth_ref;
    subpasses[0].colorAttachmentCount=1;
    subpasses[0].pColorAttachments=&color_ref;
    subpasses[0].pResolveAttachments=NULL;
}
void VulkanRenderSurface::singleDependency(){
    depens_count=1;

    uint32_t color_mask=VK_ACCESS_COLOR_ATTACHMENT_READ_BIT|VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    uint32_t depth_mask=VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT|VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    depens= (VkSubpassDependency *) malloc(sizeof(VkSubpassDependency) * depens_count);
    depens[depens_count-1].srcSubpass=VK_SUBPASS_EXTERNAL;
    depens[depens_count-1].dstSubpass=0;
    depens[depens_count-1].srcStageMask=VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    depens[depens_count-1].dstStageMask=VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    depens[depens_count-1].srcAccessMask=0;
    depens[depens_count-1].dstAccessMask=color_mask|depth_mask;
    depens[depens_count-1].dependencyFlags=0;
}
void VulkanRenderSurface::subpassDependency() {
    VkSubpassDependency deff_depen;
    depens_count=1;
    if(deffered){
        deff_depen=deffered->getDependency();
        depens_count++;
    }

}

VulkanRenderSurface::VulkanRenderSurface(){
    deffered=NULL;
    base=NULL;
}

void VulkanRenderSurface::singleAttachments() {
    attachment_count=2;
    attachments=(VkAttachmentDescription*)malloc(sizeof(VkAttachmentDescription)*2);

    VkFormat color,depth;
    base->getFormats(&color,&depth);

    attachments[0].flags=0;
    attachments[0].format=color;
    attachments[0].samples=VK_SAMPLE_COUNT_1_BIT;
    attachments[0].initialLayout=VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[0].finalLayout=VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    attachments[0].loadOp=VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[0].storeOp=VK_ATTACHMENT_STORE_OP_STORE;
    attachments[0].stencilLoadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[0].stencilStoreOp=VK_ATTACHMENT_STORE_OP_DONT_CARE;

    attachments[1].flags=0;
    attachments[1].format=depth;
    attachments[1].samples=VK_SAMPLE_COUNT_1_BIT;
    attachments[1].initialLayout=VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[1].finalLayout=VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    attachments[1].loadOp=VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[1].storeOp=VK_ATTACHMENT_STORE_OP_STORE;
    attachments[1].stencilLoadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[1].stencilStoreOp=VK_ATTACHMENT_STORE_OP_DONT_CARE;
}

void VulkanRenderSurface::createFrameBuffers() {
    uint32_t img_count;
    VkImage* imgs=base->getImages(&img_count);
    VkImageView *views=base->getImageViews();
    VkImageView depth=base->getDepthView();

    fbos= (VkFramebuffer *) malloc(sizeof(VkFramebuffer) * img_count);

    for(int i=0;i<img_count;i++){
        VkImageView attachmentViews[]={views[i],depth};

        VkFramebufferCreateInfo info={};
        info.sType=VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        info.attachmentCount=2;
        info.pAttachments=attachmentViews;
        info.flags=0;
        info.pNext=NULL;
        info.renderPass=renderpass;
        info.width=base->getWindowSize().width;
        info.height=base->getWindowSize().height;
        info.layers=1;

        pfn_vkCreateFramebuffer(base->getDevice(),&info,NULL,&fbos[i]);
    }
}
