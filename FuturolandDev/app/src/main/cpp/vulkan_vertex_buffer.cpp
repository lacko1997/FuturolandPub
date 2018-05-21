//
// Created by Lacko on 2018. 05. 21..
//

#include "vulkan_vertex_buffer.h"

void VulkanVertexBuffer::createBuffer(VulkanBase *base,VkBuffer *buffer,VkDeviceMemory *memory, uint32_t size,bool vtx_buffer) {
    uint32_t graphics_ind=base->getGraphicsIndex();

    VkBufferCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    info.flags=0;
    info.pNext=NULL;
    info.queueFamilyIndexCount=1;
    info.pQueueFamilyIndices=&graphics_ind;
    info.sharingMode=VK_SHARING_MODE_EXCLUSIVE;
    info.size=vtx_buffer?size* sizeof(float):size*sizeof(short);
    info.usage=vtx_buffer?VK_BUFFER_USAGE_VERTEX_BUFFER_BIT:VK_BUFFER_USAGE_INDEX_BUFFER_BIT;

    pfn_vkCreateBuffer(base->getDevice(),&info,NULL,buffer);

    VkPhysicalDeviceMemoryProperties props=base->getMemoryProps();

    VkMemoryPropertyFlags visible=VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT|VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    uint32_t type_index;
    VkMemoryRequirements reqs;
    pfn_vkGetBufferMemoryRequirements(base->getDevice(),*buffer,&reqs);
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
    pfn_vkAllocateMemory(base->getDevice(),&minfo,NULL,memory);
    pfn_vkBindBufferMemory(base->getDevice(),*buffer,*memory,DEV_BEG);
}

VulkanVertexBuffer::VulkanVertexBuffer(VulkanBase *base,
                                       VkBuffer vetrices, uint32_t vtx_count,
                                       VkBuffer indices, uint32_t index_count,
                                       VkBuffer instance_transform, uint32_t inst_count) {
    pbase=base;
    createBuffer(base,&vertex,&vtx_memory,vtx_count*3,true);
    createBuffer(base,&index,&ind_memory,index_count,false);
    createBuffer(base,&instances,&inst_memory,inst_count*16,true);
}

VulkanVertexBuffer::~VulkanVertexBuffer() {
    pfn_vkDestroyBuffer(pbase->getDevice(),vertex,NULL);
    pfn_vkFreeMemory(pbase->getDevice(),vtx_memory,NULL);
    pfn_vkDestroyBuffer(pbase->getDevice(),index,NULL);
    pfn_vkFreeMemory(pbase->getDevice(),ind_memory,NULL);
    pfn_vkDestroyBuffer(pbase->getDevice(),instances,NULL);
    pfn_vkFreeMemory(pbase->getDevice(),inst_memory,NULL);
}

