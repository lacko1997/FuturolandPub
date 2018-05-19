#include "vulkan_module.h"

uint32_t img_ind;

VkDevice device;
VkSwapchainKHR swapchain;
VkCommandBuffer *cmd_buffs;
VkQueue queue;
VkSemaphore submitDone;
VkSemaphore imageAcquired;

void VulkanModule::draw() {
    pfn_vkAcquireNextImageKHR(device,swapchain,UINT64_MAX,imageAcquired,VK_NULL_HANDLE,&img_ind);

    VkSubmitInfo sinfo={};
    sinfo.sType=VK_STRUCTURE_TYPE_SUBMIT_INFO;
    sinfo.pNext=NULL;
    sinfo.commandBufferCount=1;
    sinfo.pCommandBuffers=&cmd_buffs[img_ind];
    sinfo.signalSemaphoreCount=1;
    sinfo.pSignalSemaphores=&submitDone;
    sinfo.waitSemaphoreCount=1;
    sinfo.pWaitSemaphores=&imageAcquired;
    sinfo.pWaitDstStageMask=0;

    VkResult result=pfn_vkQueueSubmit(queue,1,&sinfo,VK_NULL_HANDLE);

    VkPresentInfoKHR pinfo={};
    pinfo.sType=VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    pinfo.waitSemaphoreCount=1;
    pinfo.pWaitSemaphores=&submitDone;
    pinfo.pNext=NULL;
    pinfo.pImageIndices=&img_ind;
    pinfo.pResults=&result;
    pinfo.swapchainCount=1;
    pinfo.pSwapchains=&swapchain;

    pfn_vkQueuePresentKHR(queue,&pinfo);
    __android_log_print(ANDROID_LOG_ERROR,"present","%d",result);
}

VulkanModule::VulkanModule(ANativeWindow* wnd,uint32_t width,uint32_t height) {
    base=new VulkanBase(wnd,width,height);
    surface=new VulkanRenderSurface(base);
    commander=new VulkanCommands(base,surface);

    swapchain=base->getSwapchain();
    cmd_buffs=commander->getCmdBuffs();
    commander->recordCommandBuffers(cmd_buffs);

    device=base->getDevice();
    swapchain=base->getSwapchain();
    cmd_buffs=commander->getCmdBuffs();
    queue=base->getQueue(0);

    SEMAPHORE_INFO;
    pfn_vkCreateSemaphore(base->getDevice(),&semaphore,NULL,&submitDone);
    pfn_vkCreateSemaphore(base->getDevice(),&semaphore,NULL,&imageAcquired);
}
