//
// Created by Lacko on 2018. 05. 07..
//

#ifndef FUTUROLANDDEV_VULKAN_DEFFERED_COMPONENT_H
#define FUTUROLANDDEV_VULKAN_DEFFERED_COMPONENT_H


#include "vulkan_func.h"

class VulkanDefferedComponent {
private:
    VkSubpassDescription deffered;
    VkSubpassDependency depen;
public:
    VkSubpassDependency getDependency(){return depen;}
};


#endif //FUTUROLANDDEV_VULKAN_DEFFERED_COMPONENT_H
