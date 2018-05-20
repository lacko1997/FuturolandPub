#include "vulkan_func.h"

PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr;
PFN_vkEnumerateInstanceLayerProperties pfn_vkEnumerateInstanceLayerProperties;
PFN_vkCreateInstance pfn_vkCreateInstance;
PFN_vkEnumeratePhysicalDevices pfn_vkEnumeratePhysicalDevices;
PFN_vkGetPhysicalDeviceFeatures pfn_vkGetPhysicalDeviceFeatures;
PFN_vkGetPhysicalDeviceQueueFamilyProperties pfn_vkGetPhysicalDeviceQueueFamilyProperties;
PFN_vkCreateDevice pfn_vkCreateDevice;
PFN_vkCreateAndroidSurfaceKHR pfn_vkCreateAndroidSurfaceKHR;
PFN_vkGetDeviceQueue pfn_vkGetDeviceQueue;
PFN_vkGetPhysicalDeviceProperties pfn_vkGetPhysicalDeviceProperties;
PFN_vkGetPhysicalDeviceMemoryProperties pfn_vkGetPhysicalDeviceMemoryProperties;
PFN_vkGetPhysicalDeviceSurfaceFormatsKHR pfn_vkGetPhysicalDeviceSurfaceFormatsKHR;
PFN_vkCreateSwapchainKHR pfn_vkCreateSwapchainKHR;
PFN_vkGetPhysicalDeviceSurfacePresentModesKHR pfn_vkGetPhysicalDeviceSurfacePresentModesKHR;
PFN_vkGetSwapchainImagesKHR pfn_vkGetSwapchainImagesKHR;
PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR pfn_vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
PFN_vkGetPhysicalDeviceFormatProperties pfn_vkGetPhysicalDeviceFormatProperties;
PFN_vkCreateImage pfn_vkCreateImage;
PFN_vkGetImageMemoryRequirements pfn_vkGetImageMemoryRequirements;
PFN_vkCreateImageView pfn_vkCreateImageView;
PFN_vkCreateRenderPass pfn_vkCreateRenderPass;
PFN_vkCreateFramebuffer pfn_vkCreateFramebuffer;
PFN_vkCreateCommandPool pfn_vkCreateCommandPool;
PFN_vkAllocateCommandBuffers pfn_vkAllocateCommandBuffers;
PFN_vkBeginCommandBuffer pfn_vkBeginCommandBuffer;
PFN_vkCmdBeginRenderPass pfn_vkCmdBeginRenderPass;
PFN_vkCmdBindPipeline pfn_vkCmdBindPipeline;
PFN_vkCmdBindIndexBuffer pfn_vkCmdBindIndexBuffer;
PFN_vkCmdEndRenderPass pfn_vkCmdEndRenderPass;
PFN_vkEndCommandBuffer pfn_vkEndCommandBuffer;
PFN_vkCreateSemaphore pfn_vkCreateSemaphore;
PFN_vkAcquireNextImageKHR pfn_vkAcquireNextImageKHR;
PFN_vkQueueSubmit pfn_vkQueueSubmit;
PFN_vkQueuePresentKHR pfn_vkQueuePresentKHR;
PFN_vkCreateBuffer pfn_vkCreateBuffer;
PFN_vkGetBufferMemoryRequirements pfn_vkGetBufferMemoryRequirements;
PFN_vkAllocateMemory pfn_vkAllocateMemory;
PFN_vkBindBufferMemory pfn_vkBindBufferMemory;
PFN_vkBindImageMemory pfn_vkBindImageMemory;
PFN_vkCreateSampler pfn_vkCreateSampler;
PFN_vkCreateDescriptorSetLayout pfn_vkCreateDescriptorSetLayout;
PFN_vkCreateDescriptorPool pfn_vkCreateDescriptorPool;
PFN_vkAllocateDescriptorSets pfn_vkAllocateDescriptorSets;
PFN_vkCreatePipelineLayout pfn_vkCreatePipelineLayout;
PFN_vkCreateGraphicsPipelines pfn_vkCreateGraphicsPipelines;
PFN_vkCreateShaderModule pfn_vkCreateShaderModule;
PFN_vkDestroySemaphore pfn_vkDestroySemaphore;
PFN_vkFreeMemory pfn_vkFreeMemory;
PFN_vkDestroyBuffer pfn_vkDestroyBuffer;
PFN_vkDestroyCommandPool pfn_vkDestroyCommandPool;
PFN_vkFreeCommandBuffers pfn_vkFreeCommandBuffers;
PFN_vkDestroyImage pfn_vkDestroyImage;
PFN_vkDestroyImageView pfn_vkDestroyImageView;
PFN_vkDestroySwapchainKHR pfn_vkDestroySwapchainKHR;
PFN_vkDestroySurfaceKHR pfn_vkDestroySurfaceKHR;
PFN_vkDestroyDevice pfn_vkDestroyDevice;
PFN_vkDestroyInstance pfn_vkDestroyInstance;
PFN_vkDestroyRenderPass pfn_vkDestroyRenderPass;
PFN_vkDestroyFramebuffer pfn_vkDestroyFramebuffer;
PFN_vkQueueWaitIdle pfn_vkQueueWaitIdle;
//FUTUROLAND_VULKAN_FUNC_H

void loadVulkan(void* libvulkan) {
    pfn_vkCreateInstance = (PFN_vkCreateInstance) dlsym(libvulkan, "vkCreateInstance");

    pfn_vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr) dlsym(libvulkan,
                                                                  "vkGetInstanceProcAddr");
    pfn_vkEnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties) dlsym(
            libvulkan, "vkEnumerateInstanceLayerProperties");

    pfn_vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices) dlsym(libvulkan,
                                                                            "vkEnumeratePhysicalDevices");
    pfn_vkGetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties) dlsym(
            libvulkan, "vkGetPhysicalDeviceMemoryProperties");
    pfn_vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties) dlsym(libvulkan,
                                                                                  "vkGetPhysicalDeviceProperties");
    pfn_vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties) dlsym(
            libvulkan, "vkGetPhysicalDeviceQueueFamilyProperties");
    pfn_vkGetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures) dlsym(libvulkan,
                                                                              "vkGetPhysicalDeviceFeatures");
    pfn_vkGetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR) dlsym(
            libvulkan, "vkGetPhysicalDeviceFeatures");
    pfn_vkGetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR) dlsym(
            libvulkan, "vkGetPhysicalDeviceSurfacePresentModesKHR");
    pfn_vkGetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR) dlsym(
            libvulkan, "vkGetPhysicalDeviceSurfaceFormatsKHR");

    pfn_vkCreateDevice = (PFN_vkCreateDevice) dlsym(libvulkan, "vkCreateDevice");
    pfn_vkGetDeviceQueue = (PFN_vkGetDeviceQueue) dlsym(libvulkan, "vkGetDeviceQueue");
    pfn_vkCreateAndroidSurfaceKHR = (PFN_vkCreateAndroidSurfaceKHR) dlsym(libvulkan,
                                                                          "vkCreateAndroidSurfaceKHR");
    pfn_vkCreateSwapchainKHR = (PFN_vkCreateSwapchainKHR) dlsym(libvulkan, "vkCreateSwapchainKHR");

    pfn_vkGetPhysicalDeviceFormatProperties = (PFN_vkGetPhysicalDeviceFormatProperties) dlsym(
            libvulkan, "vkGetPhysicalDeviceFormatProperties");
    pfn_vkCreateImage = (PFN_vkCreateImage) dlsym(libvulkan, "vkCreateImage");
    pfn_vkGetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements) dlsym(libvulkan,
                                                                                "vkGetImageMemoryRequirements");
    pfn_vkGetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR) dlsym(libvulkan,
                                                                      "vkGetSwapchainImagesKHR");
    pfn_vkCreateImageView = (PFN_vkCreateImageView) dlsym(libvulkan, "vkCreateImageView");
    pfn_vkCreateRenderPass = (PFN_vkCreateRenderPass) dlsym(libvulkan, "vkCreateRenderPass");
    pfn_vkCreateFramebuffer = (PFN_vkCreateFramebuffer) dlsym(libvulkan, "vkCreateFramebuffer");

    pfn_vkCreateCommandPool = (PFN_vkCreateCommandPool) dlsym(libvulkan, "vkCreateCommandPool");
    pfn_vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers) dlsym(libvulkan,
                                                                        "vkAllocateCommandBuffers");
    pfn_vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer) dlsym(libvulkan, "vkBeginCommandBuffer");
    pfn_vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass) dlsym(libvulkan, "vkCmdBeginRenderPass");
    pfn_vkCmdBindPipeline = (PFN_vkCmdBindPipeline) dlsym(libvulkan, "vkCmdBindPipeline");
    pfn_vkCmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer) dlsym(libvulkan, "vkCmdBindIndexBuffer");
    pfn_vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass) dlsym(libvulkan, "vkCmdEndRenderPass");
    pfn_vkEndCommandBuffer = (PFN_vkEndCommandBuffer) dlsym(libvulkan, "vkEndCommandBuffer");

    pfn_vkCreateSemaphore = (PFN_vkCreateSemaphore) dlsym(libvulkan, "vkCreateSemaphore");
    pfn_vkAcquireNextImageKHR = (PFN_vkAcquireNextImageKHR) dlsym(libvulkan,
                                                                  "vkAcquireNextImageKHR");
    pfn_vkQueueSubmit = (PFN_vkQueueSubmit) dlsym(libvulkan, "vkQueueSubmit");
    pfn_vkQueuePresentKHR = (PFN_vkQueuePresentKHR) dlsym(libvulkan, "vkQueuePresentKHR");

    pfn_vkCreateShaderModule = (PFN_vkCreateShaderModule) dlsym(libvulkan, "vkCreateShaderModule");

    pfn_vkCreateBuffer = (PFN_vkCreateBuffer) dlsym(libvulkan, "vkCreateBuffer");
    pfn_vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements) dlsym(libvulkan,
                                                                                  "vkGetBufferMemoryRequirements");
    pfn_vkAllocateMemory = (PFN_vkAllocateMemory) dlsym(libvulkan, "vkAllocateMemory");
    pfn_vkBindBufferMemory = (PFN_vkBindBufferMemory) dlsym(libvulkan, "vkBindBufferMemory");
    pfn_vkBindImageMemory = (PFN_vkBindImageMemory) dlsym(libvulkan, "vkBindImageMemory");
    pfn_vkCreateSampler = (PFN_vkCreateSampler) dlsym(libvulkan, "vkCreateSampler");

    pfn_vkFreeMemory = (PFN_vkFreeMemory) dlsym(libvulkan, "vkFreeMemory");

    pfn_vkDestroySemaphore= (PFN_vkDestroySemaphore) dlsym(libvulkan, "vkDestroySemaphore");
    pfn_vkQueueWaitIdle = (PFN_vkQueueWaitIdle) dlsym(libvulkan, "vkQueueWaitIdle");
    pfn_vkDestroyBuffer = (PFN_vkDestroyBuffer) dlsym(libvulkan, "vkDestroyBuffer");
    pfn_vkDestroyCommandPool= (PFN_vkDestroyCommandPool) dlsym(libvulkan, "vkDestroyCommandPool");
    pfn_vkFreeCommandBuffers= (PFN_vkFreeCommandBuffers) dlsym(libvulkan, "vkFreeCommandBuffers");
    pfn_vkDestroyRenderPass= (PFN_vkDestroyRenderPass) dlsym(libvulkan, "vkDestroyRenderPass");
    pfn_vkDestroyFramebuffer= (PFN_vkDestroyFramebuffer) dlsym(libvulkan, "vkDestroyFramebuffer");
    pfn_vkDestroyImage= (PFN_vkDestroyImage) dlsym(libvulkan, "vkDestroyImage");
    pfn_vkDestroyImageView= (PFN_vkDestroyImageView) dlsym(libvulkan, "vkDestroyImageView");
    pfn_vkDestroySwapchainKHR= (PFN_vkDestroySwapchainKHR) dlsym(libvulkan, "vkDestroySwapchainKHR");
    pfn_vkDestroySurfaceKHR= (PFN_vkDestroySurfaceKHR) dlsym(libvulkan, "vkDestroySurfaceKHR");
    pfn_vkDestroyDevice= (PFN_vkDestroyDevice) dlsym(libvulkan, "vkDestroyDevice");
    pfn_vkDestroyInstance= (PFN_vkDestroyInstance) dlsym(libvulkan, "vkDestroyInstance");
}