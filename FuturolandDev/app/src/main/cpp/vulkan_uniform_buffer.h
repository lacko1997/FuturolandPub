//
// Created by Lacko on 2018. 05. 21..
//

#ifndef FUTUROLANDDEV_VULKAN_UNIFORM_BUFFER_H
#define FUTUROLANDDEV_VULKAN_UNIFORM_BUFFER_H

#include "vulkan_base.h"

class VulkanUniformBuffer {
private:
    VulkanBase *pbase;

    VkBuffer buffer;
    VkDeviceMemory memory;
public:
    VkBuffer getBuffer(){return buffer;}
    VkDeviceMemory getMemory(){return memory;}
    VulkanUniformBuffer(VulkanBase *base,uint32_t length);
    ~VulkanUniformBuffer();
};


#endif //FUTUROLANDDEV_VULKAN_UNIFORM_BUFFER_H
