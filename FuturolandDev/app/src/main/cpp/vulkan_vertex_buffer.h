//
// Created by Lacko on 2018. 05. 21..
//

#ifndef FUTUROLANDDEV_VULKAN_VERTEX_BUFFER_H
#define FUTUROLANDDEV_VULKAN_VERTEX_BUFFER_H

#include "vulkan_base.h"

class VulkanVertexBuffer {
private:
    VulkanBase *pbase;

    VkBuffer vertex;
    VkDeviceMemory vtx_memory;
    VkBuffer index;
    VkDeviceMemory ind_memory;
    VkBuffer instances;
    VkDeviceMemory inst_memory;
    void createBuffer(VulkanBase *base,VkBuffer *buffer,VkDeviceMemory *memory,uint32_t size,bool vtx_buffer);
public:
    VulkanVertexBuffer(VulkanBase *base,VkBuffer vetrices,uint32_t vtx_count,VkBuffer indices,uint32_t index_count,VkBuffer instance_transform,uint32_t inst_count);
    ~VulkanVertexBuffer();
};


#endif //FUTUROLANDDEV_VULKAN_VERTEX_BUFFER_H
