//
// Created by Lacko on 2018. 05. 07..
//

#include "vulkan_module.h"
uint32_t img_ind;
void VulkanModule::draw() {
    pfn_vkAcquireNextImageKHR(base->getDevice(),base->getSwapchain(),UINT64_MAX,VK_NULL_HANDLE,VK_NULL_HANDLE,&img_ind);

    VkSubmitInfo sinfo={};
    sinfo.sType=VK_STRUCTURE_TYPE_SUBMIT_INFO;
    sinfo.pNext=NULL;
    sinfo.commandBufferCount=1;
    sinfo.pCommandBuffers=
    pfn_vkQueueSubmit()
}
