#include "vulkan_render_surface.h"

void VulkanRenderSurface::createRenderpass() {
    VkFormat color,depth;
    base->getFormats(&color,&depth);

    VkAttachmentDescription attachments[]={{},{}};
    attachments[0].flags=0;
    attachments[0].initialLayout=VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[0].finalLayout=VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    attachments[0].format=color;
    attachments[0].samples=VK_SAMPLE_COUNT_1_BIT;
    attachments[0].loadOp=VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[0].storeOp=VK_ATTACHMENT_STORE_OP_STORE;
    attachments[0].stencilLoadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[0].stencilStoreOp=VK_ATTACHMENT_STORE_OP_DONT_CARE;

    attachments[1].flags=0;
    attachments[1].initialLayout=VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[1].finalLayout=VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    attachments[1].format=depth;
    attachments[1].samples=VK_SAMPLE_COUNT_1_BIT;
    attachments[1].loadOp=VK_ATTACHMENT_LOAD_OP_LOAD;
    attachments[1].storeOp=VK_ATTACHMENT_STORE_OP_STORE;
    attachments[1].stencilLoadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[1].stencilStoreOp=VK_ATTACHMENT_STORE_OP_DONT_CARE;

    VkSubpassDependency depens={};
    depens.dependencyFlags=0;
    depens.srcSubpass=VK_SUBPASS_EXTERNAL;
    depens.dstSubpass=0;
    depens.srcAccessMask=0;
    depens.dstAccessMask=VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT|VK_ACCESS_COLOR_ATTACHMENT_READ_BIT|VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT|VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
    depens.srcStageMask=VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    depens.dstStageMask=VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

    VkAttachmentReference color_ref={};
    color_ref.attachment=0;
    color_ref.layout=VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkAttachmentReference depth_ref={};
    depth_ref.attachment=1;
    depth_ref.layout=VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpasses={};
    subpasses.flags=0;
    subpasses.colorAttachmentCount=1;
    subpasses.pColorAttachments=&color_ref;
    subpasses.pDepthStencilAttachment=&depth_ref;
    subpasses.inputAttachmentCount=0;
    subpasses.pInputAttachments=NULL;
    subpasses.preserveAttachmentCount=0;
    subpasses.pPreserveAttachments=NULL;
    subpasses.pResolveAttachments=NULL;

    VkRenderPassCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    info.pNext=NULL;
    info.flags=0;
    info.attachmentCount=2;
    info.pAttachments=attachments;
    info.dependencyCount=1;
    info.pDependencies=&depens;
    info.subpassCount=1;
    info.pSubpasses=&subpasses;

    /*__android_log_print(ANDROID_LOG_ERROR,"aaa","renderpass:%p subpass:%p (%d) base:%p info:%p (%d) renderpass_func:%p\n attachmnets:%p (%d) dependencies:%p (%d)",
                        &renderpass,
                        subpasses, (int)sizeof(VkSubpassDescription),
                        base,
                        &info, (int)sizeof(VkRenderPassCreateInfo),
                        pfn_vkCreateRenderPass,
                        attachments,(int)sizeof(VkAttachmentDescription),
                        depens,(int)sizeof(VkSubpassDependency)
                        );*/

    VkResult result=pfn_vkCreateRenderPass(base->getDevice(),&info,NULL,&renderpass);
}
VulkanRenderSurface::VulkanRenderSurface(VulkanBase *base):base(base){
    createRenderpass();
    createFrameBuffers();
}

void VulkanRenderSurface::createFrameBuffers() {
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
