#ifndef FUTUROLAND_VULKAN_FUNC_H
#define FUTUROLAND_VULKAN_FUNC_H

#define VK_USE_PLATFORM_ANDROID_KHR 1
#include <vulkan/vulkan.h>
#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <dlfcn.h>
#include <vector>
#include <cmath>
#include <android/log.h>

#define SEMAPHORE_INFO VkSemaphoreCreateInfo semaphore={\
.sType=VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,\
.flags=0,\
.pNext=NULL}

using namespace std;

extern PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr;
extern PFN_vkEnumerateInstanceLayerProperties pfn_vkEnumerateInstanceLayerProperties;

extern PFN_vkCreateInstance pfn_vkCreateInstance;
extern PFN_vkEnumeratePhysicalDevices pfn_vkEnumeratePhysicalDevices;
extern PFN_vkGetPhysicalDeviceFeatures pfn_vkGetPhysicalDeviceFeatures;
extern PFN_vkGetPhysicalDeviceQueueFamilyProperties pfn_vkGetPhysicalDeviceQueueFamilyProperties;
extern PFN_vkCreateDevice pfn_vkCreateDevice;
extern PFN_vkCreateAndroidSurfaceKHR pfn_vkCreateAndroidSurfaceKHR;
extern PFN_vkGetDeviceQueue pfn_vkGetDeviceQueue;

extern PFN_vkGetPhysicalDeviceProperties pfn_vkGetPhysicalDeviceProperties;
extern PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR pfn_vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
extern PFN_vkGetPhysicalDeviceMemoryProperties pfn_vkGetPhysicalDeviceMemoryProperties;
extern PFN_vkGetPhysicalDeviceSurfaceFormatsKHR pfn_vkGetPhysicalDeviceSurfaceFormatsKHR;
extern PFN_vkCreateSwapchainKHR pfn_vkCreateSwapchainKHR;
extern PFN_vkGetPhysicalDeviceSurfacePresentModesKHR pfn_vkGetPhysicalDeviceSurfacePresentModesKHR;

extern PFN_vkGetSwapchainImagesKHR pfn_vkGetSwapchainImagesKHR;
extern PFN_vkGetPhysicalDeviceFormatProperties pfn_vkGetPhysicalDeviceFormatProperties;
extern PFN_vkCreateImage pfn_vkCreateImage;
extern PFN_vkGetImageMemoryRequirements pfn_vkGetImageMemoryRequirements;
extern PFN_vkCreateImageView pfn_vkCreateImageView;
extern PFN_vkCreateRenderPass pfn_vkCreateRenderPass;
extern PFN_vkCreateFramebuffer pfn_vkCreateFramebuffer;

extern PFN_vkCreateCommandPool pfn_vkCreateCommandPool;
extern PFN_vkAllocateCommandBuffers pfn_vkAllocateCommandBuffers;
extern PFN_vkBeginCommandBuffer pfn_vkBeginCommandBuffer;
extern PFN_vkCmdBeginRenderPass pfn_vkCmdBeginRenderPass;
extern PFN_vkCmdBindPipeline pfn_vkCmdBindPipeline;
extern PFN_vkCmdBindIndexBuffer pfn_vkCmdBindIndexBuffer;
extern PFN_vkCmdEndRenderPass pfn_vkCmdEndRenderPass;
extern PFN_vkEndCommandBuffer pfn_vkEndCommandBuffer;

extern PFN_vkCreateSemaphore pfn_vkCreateSemaphore;
extern PFN_vkAcquireNextImageKHR pfn_vkAcquireNextImageKHR;
extern PFN_vkQueueSubmit pfn_vkQueueSubmit;
extern PFN_vkQueuePresentKHR pfn_vkQueuePresentKHR;

extern PFN_vkCreateShaderModule pfn_vkCreateShaderModule;

extern PFN_vkCreateBuffer pfn_vkCreateBuffer;
extern PFN_vkGetBufferMemoryRequirements pfn_vkGetBufferMemoryRequirements;
extern PFN_vkAllocateMemory pfn_vkAllocateMemory;
extern PFN_vkBindBufferMemory pfn_vkBindBufferMemory;
extern PFN_vkBindImageMemory pfn_vkBindImageMemory;
extern PFN_vkCreateSampler pfn_vkCreateSampler;
extern PFN_vkCreateDescriptorSetLayout pfn_vkCreateDescriptorSetLayout;
extern PFN_vkCreateDescriptorPool pfn_vkCreateDescriptorPool;
extern PFN_vkAllocateDescriptorSets pfn_vkAllocateDescriptorSets;
extern PFN_vkCreatePipelineLayout pfn_vkCreatePipelineLayout;
extern PFN_vkCreateGraphicsPipelines pfn_vkCreateGraphicsPipelines;

extern PFN_vkMapMemory pfn_vkMapMemory;
extern PFN_vkUnmapMemory pfn_vkUnmapMemory;

extern PFN_vkDestroySemaphore pfn_vkDestroySemaphore;
extern PFN_vkDestroyRenderPass pfn_vkDestroyRenderPass;
extern PFN_vkDestroyFramebuffer pfn_vkDestroyFramebuffer;
extern PFN_vkFreeMemory pfn_vkFreeMemory;
extern PFN_vkDestroyBuffer pfn_vkDestroyBuffer;
extern PFN_vkDestroyCommandPool pfn_vkDestroyCommandPool;
extern PFN_vkFreeCommandBuffers pfn_vkFreeCommandBuffers;
extern PFN_vkDestroyImage pfn_vkDestroyImage;
extern PFN_vkDestroyImageView pfn_vkDestroyImageView;
extern PFN_vkDestroySwapchainKHR pfn_vkDestroySwapchainKHR;
extern PFN_vkDestroySurfaceKHR pfn_vkDestroySurfaceKHR;
extern PFN_vkDestroyDevice pfn_vkDestroyDevice;
extern PFN_vkDestroyInstance pfn_vkDestroyInstance;
extern PFN_vkDestroySampler pfn_vkDestroySampler;
extern PFN_vkQueueWaitIdle pfn_vkQueueWaitIdle;

void loadVulkan(void* libvulkan);

#endif //FUTUROLAND_VULKAN_FUNC_H
