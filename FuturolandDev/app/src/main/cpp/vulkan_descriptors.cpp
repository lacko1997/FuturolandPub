//
// Created by Lacko on 2018. 05. 20..
//

#include <vulkan/vulkan.h>
#include "vulkan_descriptors.h"

VulkanDescriptors::VulkanDescriptors() {
    VkDescriptorSetLayoutBinding binding={};
    binding.binding=0;
    binding.descriptorCount=1;
    binding.descriptorType=VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

    VkDescriptorSetLayoutCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    info.pNext=NULL;
    info.flags=0;
    info.bindingCount=1;
    info.pBindings=NULL; //TODO create binding
}
