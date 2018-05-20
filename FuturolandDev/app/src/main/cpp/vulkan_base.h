#ifndef FUTUROLANDDEV_VULKAN_BASE_H
#define FUTUROLANDDEV_VULKAN_BASE_H

#include "vulkan_func.h"
//#define DEBUG

#define DEV_BEG (VkDeviceSize) 0
#define CLIPPING {\
    1.0f,0.0f,0.0f,0.0f,\
    0.0f,1.0f,0.0f,0.0f,\
    0.0f,0.0f,0.5f,0.5f,\
    0.0f,0.0f,0.0f,1.0f}
#define IDENTITY {\
1.0f,0.0f,0.0f,0.0f,\
0.0f,1.0f,0.0f,0.0f,\
0.0f,0.0f,1.0f,0.0f,\
0.0f,0.0f,0.0f,1.0f}

#define RATIO(extent) ((float)extent.width/(float)extent.height)
#define PI 3.14159265358979
#define RADIANS(alpha) (alpha*(PI/180.0f))
#define PROJECTION(fovy,ratio,zNear,zFar) {\
1.0f/(ratio*tan(fovy/2.0f)),0.0f,0.0f,0.0f,\
0.0f,1.0f/tan(fovy/2.0f),0.0f,0.0f,\
0.0f,0.0f,-(zFar+zNear)/(zFar-zNear),-1.0f,\
0.0f,0.0f,-(2.0f*zNear*zFar)/(zFar-zNear),1.0f}

class VulkanBase {
private:
#ifdef DEBUG
    PFN_vkCreateDebugReportCallbackEXT pfn_vkCreateDebugReportCallbackEXT;
    VkDebugReportCallbackEXT callback;
#endif
    VkInstance instance;
    VkPhysicalDevice gpu;
    VkDevice device;
    VkQueue queue;
    uint32_t graphics_ind;
    VkSurfaceKHR surface;
    VkSwapchainKHR swapchain;

    VkExtent2D wnd_size;
    VkPhysicalDeviceMemoryProperties mem_props;

    uint32_t img_count;
    VkImage *swImages;
    VkFormat color_format;
    VkImageView *swImgViews;

    VkImage depthBuffer;
    VkFormat depth_format;
    VkImageView depthView;
    VkDeviceMemory depth_mem;
    bool supported;

    bool createInstance(char* appname);
#ifdef DEBUG
    void createReportCallback();
#endif
    void enumerateGPU();
    void createDevice();
    void createSurface(ANativeWindow *wnd,VkExtent2D wnd_size);
    void createSwapchain();
    void reciveImages();
    void createDepthBuffer();
public:
    bool isSupported(){return supported;}
    VkInstance getInstance(){return instance;}
    VkPhysicalDevice getGpu(){return gpu;}
    VkDevice getDevice(){return device;}
    VkQueue getQueue(uint32_t index){return queue;}
    VkSurfaceKHR getSurface(){return surface;}
    VkSwapchainKHR getSwapchain(){ return swapchain;}
    VkExtent2D getWindowSize(){return wnd_size;}
    VkImage *getImages(uint32_t *count){
        *count=img_count;
        return swImages;
    }
    VkImage getDepthBuffer(){return depthBuffer;}
    VkImageView *getImageViews(){ return swImgViews;}
    VkImageView getDepthView(){return depthView;}
    void getFormats(VkFormat *color,VkFormat *depth){
        *color=color_format;
        *depth=depth_format;
    }

    uint32_t getGraphicsIndex(){return graphics_ind;}
    VkPhysicalDeviceMemoryProperties getMemoryProps(){return mem_props;}
    VkDeviceMemory getDepthMemory(){return depth_mem;}
    VulkanBase(ANativeWindow *,uint32_t width,uint32_t height);
};

#endif //FUTUROLANDDEV_VULKAN_BASE_H
