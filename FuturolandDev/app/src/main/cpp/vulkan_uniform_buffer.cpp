//
// Created by Lacko on 2018. 05. 21..
//

#include "vulkan_uniform_buffer.h"

VulkanUniformBuffer::VulkanUniformBuffer(VulkanBase *base,uint32_t length) {
    pbase=base;

    uint32_t graphics_ind=base->getGraphicsIndex();

    VkBufferCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    info.flags=0;
    info.pNext=NULL;
    info.queueFamilyIndexCount=1;
    info.pQueueFamilyIndices=&graphics_ind;
    info.sharingMode=VK_SHARING_MODE_EXCLUSIVE;
    info.size=length*sizeof(float);
    info.usage=VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
    pfn_vkCreateBuffer(base->getDevice(),&info,NULL,&buffer);

    VkPhysicalDeviceMemoryProperties props=base->getMemoryProps();

    VkMemoryPropertyFlags visible=VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT|VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    VkMemoryRequirements reqs;
    uint32_t type_index;
    pfn_vkGetBufferMemoryRequirements(base->getDevice(),buffer,&reqs);
    for(uint32_t i=0;i<props.memoryTypeCount;i++){
        if(reqs.memoryTypeBits&(1<<i)&&(props.memoryTypes[i].propertyFlags&visible)==visible){
            type_index=i;
        }
    }

    VkMemoryAllocateInfo minfo={};
    minfo.sType=VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    minfo.pNext=NULL;
    minfo.memoryTypeIndex=type_index;
    minfo.allocationSize=reqs.size;

    pfn_vkAllocateMemory(base->getDevice(),&minfo,NULL,&memory);
    pfn_vkBindBufferMemory(base->getDevice(),buffer,memory,DEV_BEG);
}

VulkanUniformBuffer::~VulkanUniformBuffer() {
    pfn_vkDestroyBuffer(pbase->getDevice(),buffer,NULL);
    pfn_vkFreeMemory(pbase->getDevice(),memory,NULL);
}
