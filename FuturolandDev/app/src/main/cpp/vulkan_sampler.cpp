//
// Created by Lacko on 2018. 05. 21..
//

#include "vulkan_sampler.h"
#include "vulkan_func.h"

VulkanSampler::VulkanSampler(VulkanBase *base) {
    pbase=base;

    VkSamplerCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    info.addressModeU=VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
    info.addressModeV=VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
    info.addressModeW=VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
    info.anisotropyEnable=VK_TRUE;
    info.borderColor=VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
    info.compareEnable=VK_FALSE;
    info.compareOp=VK_COMPARE_OP_ALWAYS;
    info.flags=0;
    info.minFilter=VK_FILTER_LINEAR;
    info.magFilter=VK_FILTER_LINEAR;
    info.maxAnisotropy=16;
    info.maxLod=0;
    info.minLod=0;
    info.mipLodBias=0;
    info.pNext=NULL;
    info.unnormalizedCoordinates=VK_FALSE;
    info.mipmapMode=VK_SAMPLER_MIPMAP_MODE_LINEAR;

    pfn_vkCreateSampler(base->getDevice(),&info,NULL,&sampler);
}

void VulkanSampler::createTexture(VulkanBase* base,void *data,uint32_t img_size) {
    VkExtent3D extent={};
    extent.width=img_size;
    extent.height=img_size;
    extent.depth=1;

    uint32_t graphics_ind=base->getGraphicsIndex();

    VkImageCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    info.arrayLayers=1;
    info.extent=extent;
    info.flags=0;
    info.format=VK_FORMAT_R8G8B8A8_UNORM;
    info.imageType=VK_IMAGE_TYPE_2D;
    info.initialLayout=VK_IMAGE_LAYOUT_UNDEFINED;
    info.mipLevels=1;
    info.pNext=NULL;
    info.queueFamilyIndexCount=1;
    info.pQueueFamilyIndices=&graphics_ind;
    info.samples=VK_SAMPLE_COUNT_1_BIT;
    info.sharingMode=VK_SHARING_MODE_EXCLUSIVE;
    info.tiling=VK_IMAGE_TILING_OPTIMAL;
    info.usage=VK_IMAGE_USAGE_SAMPLED_BIT;
    pfn_vkCreateImage(base->getDevice(),&info,NULL,&texture);

    VkPhysicalDeviceMemoryProperties props=base->getMemoryProps();

    VkMemoryPropertyFlags coherent=VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT|VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    uint32_t mem_index;
    VkMemoryRequirements reqs;
    pfn_vkGetImageMemoryRequirements(base->getDevice(),texture,&reqs);
    for(uint32_t i=0;i<props.memoryTypeCount;i++){
        if(reqs.memoryTypeBits&(1<<i)&&(props.memoryTypes[i].propertyFlags&coherent)==coherent){
            mem_index=i;
        }
    }

    VkMemoryAllocateInfo mem_info={};
    mem_info.sType=VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    mem_info.pNext=NULL;
    mem_info.memoryTypeIndex=mem_index;
    mem_info.allocationSize=reqs.size;

    pfn_vkAllocateMemory(base->getDevice(),&mem_info,NULL,&memory);
    pfn_vkBindImageMemory(base->getDevice(),texture,memory,DEV_BEG);

    void *mapped;
    pfn_vkMapMemory(base->getDevice(),memory,DEV_BEG,reqs.size,0,&mapped);
    memcpy(mapped,data,img_size*img_size);
    pfn_vkUnmapMemory(base->getDevice(),memory);

    createImageView(base);
}

void VulkanSampler::createImageView(VulkanBase *base) {
    VkComponentMapping mapping={};
    mapping.r=VK_COMPONENT_SWIZZLE_R;
    mapping.g=VK_COMPONENT_SWIZZLE_G;
    mapping.b=VK_COMPONENT_SWIZZLE_B;
    mapping.a=VK_COMPONENT_SWIZZLE_A;

    VkImageSubresourceRange range={};
    range.aspectMask=VK_IMAGE_ASPECT_COLOR_BIT;
    range.baseArrayLayer=0;
    range.baseMipLevel=0;
    range.layerCount=1;
    range.levelCount=1;

    VkImageViewCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    info.components=mapping;
    info.flags=0;
    info.format=VK_FORMAT_R8G8B8A8_UNORM;
    info.image=texture;
    info.pNext=NULL;
    info.viewType=VK_IMAGE_VIEW_TYPE_2D;
    info.subresourceRange=range;
    pfn_vkCreateImageView(base->getDevice(),&info,NULL,&view);
}

VulkanSampler::~VulkanSampler() {
    pfn_vkDestroyImage(pbase->getDevice(),texture,NULL);
    pfn_vkFreeMemory(pbase->getDevice(),memory,NULL);
    pfn_vkDestroySampler(pbase->getDevice(),sampler,NULL);
}

