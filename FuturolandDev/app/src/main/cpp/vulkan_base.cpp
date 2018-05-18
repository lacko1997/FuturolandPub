#include "vulkan_base.h"

//2018. 05. 06..
bool VulkanBase::createInstance(char* appname) {
    VkApplicationInfo app_info={};
    app_info.sType=VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pNext=NULL;
    app_info.apiVersion=VK_MAKE_VERSION(1,0,41);
    app_info.applicationVersion=VK_MAKE_VERSION(0,1,0);
    app_info.engineVersion=VK_MAKE_VERSION(0,1,0);
    app_info.pApplicationName=appname;
    app_info.pEngineName="Phenyl Engine";

    vector<char*> ext=vector<char*>();
    ext.push_back((char *const &) VK_KHR_SURFACE_EXTENSION_NAME);
    ext.push_back((char *const &) VK_KHR_ANDROID_SURFACE_EXTENSION_NAME);

    VkInstanceCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    info.pNext=NULL;
    info.enabledExtensionCount=(uint32_t)ext.size();
    info.ppEnabledExtensionNames= (const char *const *) ext.data();
    info.enabledLayerCount=0;
    info.ppEnabledLayerNames=0;
    info.pApplicationInfo=&app_info;
    VkResult result=pfn_vkCreateInstance(&info,NULL,&instance);
    return result==VK_SUCCESS;
}

void VulkanBase::enumerateGPU() {
    uint32_t one;
    pfn_vkEnumeratePhysicalDevices(instance,&one,NULL);
    VkPhysicalDevice *gpus=(VkPhysicalDevice*)malloc(sizeof(VkPhysicalDevice)*one);
    pfn_vkEnumeratePhysicalDevices(instance,&one,gpus);
    gpu=gpus[0];

    pfn_vkGetPhysicalDeviceMemoryProperties(gpu,&mem_props);

    free(gpus);

    uint32_t prop_count;
    pfn_vkGetPhysicalDeviceQueueFamilyProperties(gpu,&prop_count,NULL);
    VkQueueFamilyProperties *props=(VkQueueFamilyProperties*)malloc(sizeof(VkQueueFamilyProperties)*prop_count);
    pfn_vkGetPhysicalDeviceQueueFamilyProperties(gpu,&prop_count,props);

    bool found=false;
    for(uint32_t i=0;i<prop_count;i++){
        if(props[i].queueFlags&VK_QUEUE_GRAPHICS_BIT){
            graphics_ind=i;
            found=true;
            break;
        }
    }
    if(found){
        //success
    }
    free(props);
}

void VulkanBase::createDevice() {
    float queues[]={1.0f};

    VkDeviceQueueCreateInfo qinfo={};
    qinfo.sType=VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    qinfo.queueCount=1;
    qinfo.queueFamilyIndex=graphics_ind;
    qinfo.pNext=NULL;
    qinfo.flags=0;
    qinfo.pQueuePriorities=queues;

    vector<char*>ext=vector<char*>();
    ext.push_back((char *const &) VK_KHR_SWAPCHAIN_EXTENSION_NAME);

    VkDeviceCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    info.flags=0;
    info.enabledLayerCount=0;
    info.ppEnabledLayerNames=NULL;
    info.enabledExtensionCount= (uint32_t) ext.size();
    info.ppEnabledExtensionNames= (const char *const *) ext.data();
    info.queueCreateInfoCount=1;
    info.pQueueCreateInfos=&qinfo;
    info.pNext=NULL;

    pfn_vkCreateDevice(gpu,&info,NULL,&device);
}

void VulkanBase::createSurface(ANativeWindow *wnd,VkExtent2D wndSize) {
    wnd_size=wndSize;

    VkAndroidSurfaceCreateInfoKHR info={};
    info.sType=VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    info.flags=0;
    info.pNext=NULL;
    info.window=wnd;

    pfn_vkCreateAndroidSurfaceKHR(instance,&info,NULL,&surface);

    pfn_vkGetDeviceQueue(device,graphics_ind,0,&queue);
}

void VulkanBase::createSwapchain() {
    uint32_t count;
    pfn_vkGetPhysicalDeviceSurfaceFormatsKHR(gpu,surface,&count,NULL);
    VkSurfaceFormatKHR *fprops= (VkSurfaceFormatKHR *) malloc(sizeof(VkSurfaceFormatKHR) * count);
    color_format=VK_FORMAT_R8G8B8A8_UNORM;
    bool ffound=false;
    for(uint32_t i=0;i<count;i++){
        if(fprops[i].format==color_format){
            ffound=true;
            break;
        }
    }
    if(!ffound){
        color_format=fprops[0].format;
    }

    free(fprops);

    VkSwapchainCreateInfoKHR info={};
    info.sType=VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    info.clipped=VK_FALSE;
    info.compositeAlpha=VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    info.flags=0;
    info.imageArrayLayers=1;
    info.imageColorSpace=VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    info.imageExtent=wnd_size;
    info.imageFormat=color_format;
    info.imageSharingMode=VK_SHARING_MODE_EXCLUSIVE;
    info.imageUsage=VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    info.minImageCount=2;
    info.oldSwapchain=VK_NULL_HANDLE;
    info.pNext=NULL;
    info.queueFamilyIndexCount=1;
    info.pQueueFamilyIndices=&graphics_ind;
    info.surface=surface;
    info.presentMode=VK_PRESENT_MODE_MAILBOX_KHR;
    info.preTransform=VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;

    pfn_vkCreateSwapchainKHR(device,&info,NULL,&swapchain);

}

void VulkanBase::reciveImages() {
    uint32_t count;
    pfn_vkGetSwapchainImagesKHR(device,swapchain,&count,NULL);
    swImages= (VkImage *) malloc(sizeof(VkImage) * count);
    pfn_vkGetSwapchainImagesKHR(device,swapchain,&count,swImages);

    swImgViews= (VkImageView *) malloc(sizeof(VkImageView) * count);

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

    for(int i=0;i<count;i++){
        VkImageViewCreateInfo info={};
        info.sType=VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        info.components=mapping;
        info.flags=0;
        info.format=color_format;
        info.image=swImages[i];
        info.pNext=NULL;
        info.subresourceRange=range;
        info.viewType=VK_IMAGE_VIEW_TYPE_2D;

        VkResult result=pfn_vkCreateImageView(device,&info,NULL,&swImgViews[i]);
        __android_log_print(ANDROID_LOG_ERROR,"valami","%d",result);
    }
}

void VulkanBase::createDepthBuffer() {
    VkFormat depth_formats[]={
            VK_FORMAT_D16_UNORM,
            VK_FORMAT_D16_UNORM_S8_UINT,
            VK_FORMAT_D24_UNORM_S8_UINT,
            VK_FORMAT_D32_SFLOAT,
            VK_FORMAT_D32_SFLOAT_S8_UINT
    };

    VkFormatProperties props;
    pfn_vkGetPhysicalDeviceFormatProperties(gpu,VK_FORMAT_D32_SFLOAT,&props);

    bool dfound = (bool) (props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);

    if(!dfound) {
        for (int i = 4; i >= 0; i--) {
            if(props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT){
                dfound=true;
                depth_format=depth_formats[i];
            }
        }
    }

    VkExtent3D img_size={};
    img_size.width=wnd_size.width;
    img_size.height=wnd_size.height;
    img_size.depth=1;

    VkImageCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    info.arrayLayers=1;
    info.tiling=VK_IMAGE_TILING_OPTIMAL;
    info.usage=VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    info.extent=img_size;
    info.flags=0;
    info.format=depth_format;
    info.imageType=VK_IMAGE_TYPE_2D;
    info.initialLayout=VK_IMAGE_LAYOUT_UNDEFINED;
    info.mipLevels=1;
    info.pNext=NULL;
    info.queueFamilyIndexCount=1;
    info.pQueueFamilyIndices=&graphics_ind;
    info.samples=VK_SAMPLE_COUNT_1_BIT;
    info.sharingMode=VK_SHARING_MODE_EXCLUSIVE;

    pfn_vkCreateImage(device,&info,NULL,&depthBuffer);

    VkMemoryRequirements reqs={};
    pfn_vkGetImageMemoryRequirements(device,depthBuffer,&reqs);

    uint32_t local=VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

    uint32_t index;
    for(uint32_t i=0;i<mem_props.memoryTypeCount;i++){
        if(reqs.memoryTypeBits&(1<<i)&&(mem_props.memoryTypes[i].propertyFlags&local)==local){
            index=i;
        }
    }

    VkMemoryAllocateInfo mem_info={};
    mem_info.sType=VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    mem_info.pNext=NULL;
    mem_info.memoryTypeIndex=index;
    mem_info.allocationSize=reqs.size;

    pfn_vkAllocateMemory(device,&mem_info,NULL,&depth_mem);
    pfn_vkBindImageMemory(device,depthBuffer,depth_mem,DEV_BEG);

    VkComponentMapping dmapping={};
    dmapping.r=VK_COMPONENT_SWIZZLE_R;
    dmapping.g=VK_COMPONENT_SWIZZLE_G;
    dmapping.b=VK_COMPONENT_SWIZZLE_B;
    dmapping.a=VK_COMPONENT_SWIZZLE_A;

    VkImageSubresourceRange drange;
    drange.aspectMask=VK_IMAGE_ASPECT_DEPTH_BIT;
    drange.baseMipLevel=0;
    drange.baseArrayLayer=0;
    drange.layerCount=1;
    drange.levelCount=1;

    VkImageViewCreateInfo vinfo={};
    vinfo.sType=VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    vinfo.components=dmapping;
    vinfo.flags=0;
    vinfo.format=depth_format;
    vinfo.image=depthBuffer;
    vinfo.pNext=NULL;
    vinfo.viewType=VK_IMAGE_VIEW_TYPE_2D;
    vinfo.subresourceRange=drange;

    pfn_vkCreateImageView(device,&vinfo,NULL,&depthView);
}

VulkanBase::VulkanBase(ANativeWindow *wnd,uint32_t width,uint32_t height) {
    VkExtent2D wnd_size={};
    wnd_size.width=width;
    wnd_size.height=height;

    bool supported=createInstance((char *) "Futuroland");
    enumerateGPU();
    createDevice();
    createSurface(wnd,wnd_size);
    createSwapchain();
    reciveImages();
    createDepthBuffer();
}

