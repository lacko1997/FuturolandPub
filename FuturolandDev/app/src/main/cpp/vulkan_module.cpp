#include "vulkan_module.h"

uint32_t img_ind;

VkDevice device;
VkSwapchainKHR swapchain;
VkCommandBuffer *cmd_buffs;
VkQueue queue;
VkSemaphore submitDone;

void VulkanModule::draw() {
    pfn_vkAcquireNextImageKHR(device,swapchain,UINT64_MAX,VK_NULL_HANDLE,VK_NULL_HANDLE,&img_ind);

    VkSubmitInfo sinfo={};
    sinfo.sType=VK_STRUCTURE_TYPE_SUBMIT_INFO;
    sinfo.pNext=NULL;
    sinfo.commandBufferCount=1;
    sinfo.pCommandBuffers=&cmd_buffs[img_ind];
    sinfo.signalSemaphoreCount=1;
    sinfo.pSignalSemaphores=&submitDone;
    sinfo.waitSemaphoreCount=0;
    sinfo.pWaitSemaphores=NULL;
    sinfo.pWaitDstStageMask=NULL;

    pfn_vkQueueSubmit(queue,1,&sinfo,VK_NULL_HANDLE);

    VkPresentInfoKHR pinfo={};
    pinfo.sType=VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    pinfo.waitSemaphoreCount=1;
    pinfo.pWaitSemaphores=&submitDone;
    pinfo.pNext=NULL;
    pinfo.pImageIndices=&img_ind;
    pinfo.pResults=NULL;
    pinfo.swapchainCount=1;
    pinfo.pSwapchains=&swapchain;

    pfn_vkQueuePresentKHR(queue,&pinfo);
}

VulkanModule::VulkanModule(ANativeWindow* wnd,uint32_t width,uint32_t height) {
    base=new VulkanBase(wnd,width,height);
    surface=new VulkanRenderSurface(base);
    commander=new VulkanCommands(base,surface);

    swapchain=base->getSwapchain();
    cmd_buffs=commander->getCmdBuffs();

    device=base->getDevice();
    swapchain=base->getSwapchain();
    cmd_buffs=commander->getCmdBuffs();
    queue=base->getQueue(0);

    SEMAPHORE_INFO;
    pfn_vkCreateSemaphore(base->getDevice(),&semaphore,NULL,&submitDone);
}
