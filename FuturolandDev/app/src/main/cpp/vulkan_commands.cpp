//
// Created by Lacko on 2018. 05. 07..
//

#include "vulkan_commands.h"

void VulkanComands::createCommandPool() {
    VkCommandPoolCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    info.pNext=NULL;
    info.flags=VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    info.queueFamilyIndex=base->getGraphicsIndex();

    pfn_vkCreateCommandPool(base->getDevice(),&info,NULL,&pool);
}

VkCommandBuffer *VulkanComands::allocateCmdBuffs() {
    base->getImages(&img_count);
    VkCommandBuffer *cmdbuffer= (VkCommandBuffer*) malloc(sizeof(VkCommandBuffer) * img_count);

    VkCommandBufferAllocateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    info.pNext=NULL;
    info.commandBufferCount=2;
    info.commandPool=pool;
    info.level=VK_COMMAND_BUFFER_LEVEL_PRIMARY;

    pfn_vkAllocateCommandBuffers(base->getDevice(),&info,cmdbuffer);
}

void VulkanComands::recordCommandBuffers(VkCommandBuffer *cmd_buff) {
    VkCommandBufferBeginInfo info={};
    info.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    info.flags=VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
    info.pNext=NULL;
    info.pInheritanceInfo=NULL;

    VkClearValue values[4]={{1.0,0.0,0.0f,1.0f},{0.0f,0},{0.0,1.0,1.0f,1.0f},{1.0f,0}};

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
        rinfo.framebuffer=renderer->getFramebuffers(&img_count)[i];
        rinfo.renderArea=rect;

        pfn_vkBeginCommandBuffer(cmd_buff[i],&info);
        pfn_vkCmdBeginRenderPass(cmd_buff[i],&rinfo,VK_SUBPASS_CONTENTS_INLINE);
        pfn_vkCmdEndRenderPass(cmd_buff[i]);
        pfn_vkEndCommandBuffer(cmd_buff[i]);
    }
}


