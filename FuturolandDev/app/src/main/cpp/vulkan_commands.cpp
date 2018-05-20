#include "vulkan_commands.h"

void VulkanCommands::createCommandPool() {
    VkCommandPoolCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    info.pNext=NULL;
    info.flags=VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    info.queueFamilyIndex=base->getGraphicsIndex();

    pfn_vkCreateCommandPool(base->getDevice(),&info,NULL,&pool);
}

void VulkanCommands::allocateCmdBuffs() {
    img_count=renderer->getImgCount();
    cmd_buffs= (VkCommandBuffer*) malloc(sizeof(VkCommandBuffer) * img_count);

    VkCommandBufferAllocateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    info.pNext=NULL;
    info.commandBufferCount=img_count;
    info.commandPool=pool;
    info.level=VK_COMMAND_BUFFER_LEVEL_PRIMARY;

    pfn_vkAllocateCommandBuffers(base->getDevice(),&info,cmd_buffs);
}

void VulkanCommands::recordCommandBuffers(VkCommandBuffer *cmd_buff) {
    VkCommandBufferBeginInfo info={};
    info.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    info.flags=VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
    info.pNext=NULL;
    info.pInheritanceInfo=NULL;

    VkClearValue values[6];
    values[0].color=(VkClearColorValue){1.0,1.0,1.0,1.0};
    values[1].depthStencil=(VkClearDepthStencilValue){0.0,0};
    values[2].color=(VkClearColorValue){0.0,0.0,0.0,1.0};
    values[3].depthStencil=(VkClearDepthStencilValue){0.0,0};
    values[4].color=(VkClearColorValue){0.0,1.0,0.0,1.0};
    values[5].depthStencil=(VkClearDepthStencilValue){0.0,0};

    VkRect2D rect={};
    rect.offset.x=0;
    rect.offset.y=0;
    rect.extent=base->getWindowSize();

    for(int i=0;i<img_count;i++) {
        VkRenderPassBeginInfo rinfo={};
        rinfo.sType=VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        rinfo.pNext=NULL;
        rinfo.renderPass=renderer->getRenderpass();
        rinfo.clearValueCount=2;
        rinfo.pClearValues=&values[i*2];
        rinfo.framebuffer=renderer->getFramebuffers()[i];
        rinfo.renderArea=rect;

        pfn_vkBeginCommandBuffer(cmd_buff[i],&info);
        pfn_vkCmdBeginRenderPass(cmd_buff[i],&rinfo,VK_SUBPASS_CONTENTS_INLINE);
        pfn_vkCmdEndRenderPass(cmd_buff[i]);
        pfn_vkEndCommandBuffer(cmd_buff[i]);
    }
}

VulkanCommands::VulkanCommands(VulkanBase *base, VulkanRenderSurface *renderer):base(base),renderer(renderer) {
    createCommandPool();
    allocateCmdBuffs();
}

VulkanCommands::~VulkanCommands() {
    pfn_vkFreeCommandBuffers(base->getDevice(),pool,img_count,cmd_buffs);
    free(cmd_buffs);
    pfn_vkDestroyCommandPool(base->getDevice(),pool,NULL);
}


