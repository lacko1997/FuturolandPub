//
// Created by Lacko on 2018. 05. 21..
//

#ifndef FUTUROLANDDEV_VULKAN_SAMPLER_H
#define FUTUROLANDDEV_VULKAN_SAMPLER_H

#include "vulkan_base.h"

class VulkanSampler {
private:
    VulkanBase *pbase;

    VkSampler sampler;
    VkImage texture;
    VkImageView view;
    VkDeviceMemory memory;
    void createImageView(VulkanBase* base);
public:
    void createTexture(VulkanBase *base,void* data,uint32_t image_size);
    void setImage(VkImage image,VkImageView image_view,VkDeviceMemory image_memory){
        memory=image_memory;
        texture=image;
        view=image_view;
    }
    VkImageView getView(){return view;}
    VulkanSampler(VulkanBase* base);
    ~VulkanSampler();
};


#endif //FUTUROLANDDEV_VULKAN_SAMPLER_H
