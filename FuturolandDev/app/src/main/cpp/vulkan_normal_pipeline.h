//
// Created by Lacko on 2018. 05. 20..
//

#ifndef FUTUROLANDDEV_VULKAN_NORMAL_PIPELINE_H
#define FUTUROLANDDEV_VULKAN_NORMAL_PIPELINE_H

#include "vulkan_render_surface.h"

class NormalPipeline {
private:
    float clipping_mat[16]=CLIPPING;
    VkSpecializationMapEntry clipEntry={};
    VkSpecializationInfo spec={};

    VkPipelineVertexInputStateCreateInfo vtx_info={};
    VkVertexInputAttributeDescription *vtx_attr;
    VkVertexInputBindingDescription *vtx_binding;

    VkPipelineInputAssemblyStateCreateInfo asm_info={};

    VkPipelineTessellationStateCreateInfo tess_info={};
    uint32_t tess_count;

    VkPipelineViewportStateCreateInfo view_info={};
    VkViewport viewport;
    VkRect2D scissor;

    VkPipelineRasterizationStateCreateInfo rast_info={};

    VkPipelineMultisampleStateCreateInfo multi_info={};

    VkPipelineDepthStencilStateCreateInfo depth_info={};

    VkPipelineColorBlendStateCreateInfo color_info={};
    VkPipelineColorBlendAttachmentState color_att={};

    VkPipelineDynamicStateCreateInfo dyn_info={};

    VulkanBase *base;
    VulkanRenderSurface *surface;

    uint32_t shader_count;
    uint32_t attrib_count;

    VkShaderModule vertexSh=VK_NULL_HANDLE;
    VkShaderModule tesscSh=VK_NULL_HANDLE;
    VkShaderModule tesseSh=VK_NULL_HANDLE;
    VkShaderModule geometrySh=VK_NULL_HANDLE;
    VkShaderModule fragmentSh=VK_NULL_HANDLE;

    VkPipelineShaderStageCreateInfo *collectStages();
    void vertexInput();
    void assemble();
    void tesselation();
    void viewportInfo();
    void rasterize();
    void multisample();
    void depthTesting();
    void colorblend();
    void dynamicState();
public:
    void setVertexShader(uint32_t size,uint32_t* code);
    void setTessControlShader(uint32_t size,uint32_t* code);
    void setTessEvaluationShader(uint32_t size,uint32_t* code);
    void setGeometryShader(uint32_t size,uint32_t* code);
    void setFragmentShader(uint32_t size,uint32_t* code);

    void setTesselationControlpointCount(uint32_t count){tess_count=count;}

    void createPipeline();
    NormalPipeline(VulkanBase *base,VulkanRenderSurface *surface);
};


#endif //FUTUROLANDDEV_PIPELINE_H
