#include "vulkan_render_surface.h"

void VulkanRenderSurface::createRenderpass() {
    VkRenderPassCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    info.pNext=NULL;
    info.flags=0;
    info.attachmentCount=attachment_count;
    info.pAttachments=attachments;
    info.dependencyCount=depens_count;
    info.pDependencies=depens;
    info.subpassCount=subpass_count;
    info.pSubpasses=subpasses;

    __android_log_print(ANDROID_LOG_ERROR,"aaa","renderpass:%p subpass:%p (%d) base:%p info:%p (%d) renderpass_func:%p\n attachmnets:%p (%d) dependencies:%p (%d)",
                        &renderpass,
                        subpasses, (int)sizeof(VkSubpassDescription),
                        base,
                        &info, (int)sizeof(VkRenderPassCreateInfo),
                        pfn_vkCreateRenderPass,
                        attachments,(int)sizeof(VkAttachmentDescription),
                        depens,(int)sizeof(VkSubpassDependency)
                        );

    pfn_vkCreateRenderPass(base->getDevice(),&info,NULL,&renderpass);
    __android_log_print(ANDROID_LOG_ERROR,"aaa","aaa");
}

void VulkanRenderSurface::singleSubpass() {
    subpass_count=1;

    VkAttachmentReference color={};
    color.attachment=0;
    color.layout=VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkAttachmentReference depth={};
    color.attachment=1;
    color.layout=VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    subpasses=(VkSubpassDescription*)malloc(sizeof(VkSubpassDescription)*subpass_count);
    subpasses[0].flags=0;
    subpasses[0].colorAttachmentCount=1;
    subpasses[0].pColorAttachments=&color;
    subpasses[0].pDepthStencilAttachment=&depth;
    subpasses[0].inputAttachmentCount=0;
    subpasses[0].pInputAttachments=NULL;
    subpasses[0].preserveAttachmentCount=0;
    subpasses[0].pPreserveAttachments=NULL;
    subpasses[0].pResolveAttachments=NULL;
    subpasses[0].pipelineBindPoint=VK_PIPELINE_BIND_POINT_GRAPHICS;
}
void VulkanRenderSurface::singleDependency(){
    depens_count=1;

    depens=(VkSubpassDependency*)malloc(sizeof(VkSubpassDependency)*depens_count);
    depens[0].srcSubpass=VK_SUBPASS_EXTERNAL;
    depens[0].dstSubpass=0;
    depens[0].srcStageMask=VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    depens[0].dstStageMask=VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    depens[0].srcAccessMask=0;
    depens[0].dstAccessMask=VK_ACCESS_COLOR_ATTACHMENT_READ_BIT|VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT|
                            VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT|VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    depens[0].dependencyFlags=0;
}
void VulkanRenderSurface::subpassDependency() {

}
void VulkanRenderSurface::singleAttachments() {
    attachment_count=2;

    VkFormat color,depth;
    base->getFormats(&color,&depth);

    attachments=(VkAttachmentDescription*)malloc(sizeof(VkAttachmentDescription)*attachment_count);
    attachments[0].flags=0;
    attachments[0].finalLayout=VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    attachments[0].initialLayout=VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[0].samples=VK_SAMPLE_COUNT_1_BIT;
    attachments[0].loadOp=VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[0].storeOp=VK_ATTACHMENT_STORE_OP_STORE;
    attachments[0].stencilLoadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[0].stencilStoreOp=VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[0].format=color;

    attachments[1].flags=0;
    attachments[1].finalLayout=VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    attachments[1].initialLayout=VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[1].samples=VK_SAMPLE_COUNT_1_BIT;
    attachments[1].loadOp=VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[1].storeOp=VK_ATTACHMENT_STORE_OP_STORE;
    attachments[1].stencilLoadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[1].stencilStoreOp=VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[1].format=depth;
}

VulkanRenderSurface::VulkanRenderSurface(VulkanBase *base):base(base){
    deffered=NULL;
    singleAttachments();
    singleDependency();
    singleSubpass();

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
