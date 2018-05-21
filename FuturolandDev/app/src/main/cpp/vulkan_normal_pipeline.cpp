//2018. 05. 20..
#include "vulkan_normal_pipeline.h"

NormalPipeline::NormalPipeline(VulkanBase *base,VulkanRenderSurface *surface):base(base),surface(surface) {
    range.offset=0;
    range.size=128;
    range.stageFlags=VK_SHADER_STAGE_VERTEX_BIT;

    VkPipelineLayoutCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    info.flags=0;
    info.pNext=NULL;
    info.pushConstantRangeCount=1;
    info.pPushConstantRanges=&range;
    info.setLayoutCount=1;
    info.pSetLayouts=NULL;//TODO create descriptorset layout
}
void NormalPipeline::createPipeline(){
    VkPipelineShaderStageCreateInfo *stages=collectStages();
    vertexInput();
    assemble();
    tesselation();
    viewportInfo();
    multisample();
    depthTesting();
    colorblend();
    dynamicState();

    VkGraphicsPipelineCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    info.pNext=NULL;
    info.flags=0;
    info.stageCount=shader_count;
    info.pStages=stages;
    info.pVertexInputState=&vtx_info;
    info.pInputAssemblyState=&asm_info;
    info.pTessellationState=&tess_info;
    info.pViewportState=&view_info;
    info.pRasterizationState=&rast_info;
    info.pMultisampleState=&multi_info;
    info.pDepthStencilState=&depth_info;
    info.pColorBlendState=&color_info;
    info.pDynamicState=&dyn_info;
    info.layout;
    info.renderPass=surface->getRenderpass();
    info.subpass=0;
    info.basePipelineHandle=VK_NULL_HANDLE;
    info.basePipelineIndex=-1;
}
void NormalPipeline::setVertexShader(uint32_t size, uint32_t *code) {
    VkShaderModuleCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    info.flags=0;
    info.codeSize=size;
    info.pCode=code;
    info.pNext=NULL;

    pfn_vkCreateShaderModule(base->getDevice(),&info,NULL,&vertexSh);
}
void NormalPipeline::setTessControlShader(uint32_t size, uint32_t *code) {
    VkShaderModuleCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    info.flags=0;
    info.codeSize=size;
    info.pCode=code;
    info.pNext=NULL;

    pfn_vkCreateShaderModule(base->getDevice(),&info,NULL,&tesscSh);
}
void NormalPipeline::setTessEvaluationShader(uint32_t size, uint32_t *code) {
    VkShaderModuleCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    info.flags=0;
    info.codeSize=size;
    info.pCode=code;
    info.pNext=NULL;

    pfn_vkCreateShaderModule(base->getDevice(),&info,NULL,&tesseSh);
}
void NormalPipeline::setGeometryShader(uint32_t size, uint32_t *code) {
    VkShaderModuleCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    info.flags=0;
    info.codeSize=size;
    info.pCode=code;
    info.pNext=NULL;

    pfn_vkCreateShaderModule(base->getDevice(),&info,NULL,&geometrySh);
}
void NormalPipeline::setFragmentShader(uint32_t size, uint32_t *code) {
    VkShaderModuleCreateInfo info={};
    info.sType=VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    info.flags=0;
    info.codeSize=size;
    info.pCode=code;
    info.pNext=NULL;

    pfn_vkCreateShaderModule(base->getDevice(),&info,NULL,&fragmentSh);
}

VkPipelineShaderStageCreateInfo *NormalPipeline::collectStages() {
    shader_count=2;
    if(!fragmentSh||!vertexSh){
        __android_log_print(ANDROID_LOG_ERROR,"NormalPipeline","%d: Missing fragment or vertex shader.",__LINE__);
        return NULL;
    }
    if((!tesscSh&&tesseSh)||(tesscSh&&!tesseSh)){
        __android_log_print(ANDROID_LOG_ERROR,"NormalPipeline","%d: Tessellation control shader without Tessellation evaluation shader or vice versa.");
        return NULL;
    }
    if(tesscSh&&tesseSh){
       shader_count+=2;
    }
    if(geometrySh){
        shader_count++;
    }
    VkPipelineShaderStageCreateInfo *stages= (VkPipelineShaderStageCreateInfo *) malloc(sizeof(VkPipelineShaderStageCreateInfo) * shader_count);
    uint8_t at=0;

    clipEntry.size=64;
    clipEntry.offset=0;
    clipEntry.constantID=0;

    spec.dataSize=64;
    spec.mapEntryCount=1;
    spec.pMapEntries=&clipEntry;
    spec.pData=clipping_mat;

    stages[at].sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[at].module=vertexSh;
    stages[at].pName="main";
    stages[at].pNext=NULL;
    stages[at].stage=VK_SHADER_STAGE_VERTEX_BIT;
    stages[at].pSpecializationInfo=&spec;
    stages[at].flags=0;
    at++;

    if(tesscSh&&tesseSh){
        stages[at].sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        stages[at].flags=0;
        stages[at].module=tesscSh;
        stages[at].pName="main";
        stages[at].pNext=NULL;
        stages[at].pSpecializationInfo=NULL;
        stages[at].stage=VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
        at++;

        stages[at].sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        stages[at].flags=0;
        stages[at].module=tesseSh;
        stages[at].pName="main";
        stages[at].pNext=NULL;
        stages[at].pSpecializationInfo=NULL;
        stages[at].stage=VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
        at++;
    }
    if(geometrySh){
        stages[at].sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        stages[at].flags=0;
        stages[at].module=geometrySh;
        stages[at].pName="main";
        stages[at].pNext=NULL;
        stages[at].pSpecializationInfo=NULL;
        stages[at].stage=VK_SHADER_STAGE_GEOMETRY_BIT;
        at++;
    }

    stages[at].sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[at].flags=0;
    stages[at].module=fragmentSh;
    stages[at].pName="main";
    stages[at].pNext=NULL;
    stages[at].pSpecializationInfo=NULL;
    stages[at].stage=VK_SHADER_STAGE_GEOMETRY_BIT;
    return stages;
}

void NormalPipeline::vertexInput() {
    attrib_count=7;

    vtx_attr= (VkVertexInputAttributeDescription *) malloc(sizeof(VkVertexInputAttributeDescription) * attrib_count);
    vtx_binding=(VkVertexInputBindingDescription*)malloc(sizeof(VkVertexInputBindingDescription)*2);

    vtx_binding[0].binding=0;
    vtx_binding[0].inputRate=VK_VERTEX_INPUT_RATE_VERTEX;
    vtx_binding[0].stride=32;

    vtx_binding[1].binding=1;
    vtx_binding[1].inputRate=VK_VERTEX_INPUT_RATE_INSTANCE;
    vtx_binding[1].stride=64;

    vtx_attr[0].offset=0;
    vtx_attr[0].binding=0;
    vtx_attr[0].format=VK_FORMAT_R32G32B32_SFLOAT;
    vtx_attr[0].location=0;

    vtx_attr[1].offset=12;
    vtx_attr[1].binding=0;
    vtx_attr[1].format=VK_FORMAT_R32G32_SFLOAT;
    vtx_attr[1].location=1;

    vtx_attr[2].offset=20;
    vtx_attr[2].binding=0;
    vtx_attr[2].format=VK_FORMAT_R32G32B32_SFLOAT;
    vtx_attr[2].location=2;

    vtx_attr[3].offset=0;
    vtx_attr[3].binding=1;
    vtx_attr[3].format=VK_FORMAT_R32G32B32A32_SFLOAT;
    vtx_attr[3].location=3;

    vtx_attr[4].offset=16;
    vtx_attr[4].binding=1;
    vtx_attr[4].format=VK_FORMAT_R32G32B32A32_SFLOAT;
    vtx_attr[4].location=4;

    vtx_attr[5].offset=32;
    vtx_attr[5].binding=1;
    vtx_attr[5].format=VK_FORMAT_R32G32B32A32_SFLOAT;
    vtx_attr[5].location=5;

    vtx_attr[6].offset=48;
    vtx_attr[6].binding=1;
    vtx_attr[6].format=VK_FORMAT_R32G32B32A32_SFLOAT;
    vtx_attr[6].location=6;

    vtx_info.sType=VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vtx_info.flags=0;
    vtx_info.pNext=NULL;
    vtx_info.vertexAttributeDescriptionCount=attrib_count;
    vtx_info.pVertexAttributeDescriptions=vtx_attr;
    vtx_info.vertexBindingDescriptionCount=2;
    vtx_info.pVertexBindingDescriptions=vtx_binding;
}

void NormalPipeline::assemble() {
    asm_info.sType=VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    asm_info.flags=0;
    asm_info.pNext=NULL;
    asm_info.primitiveRestartEnable=VK_FALSE;
    asm_info.topology=VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
}

void NormalPipeline::tesselation() {
    tess_info.sType=VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
    tess_info.flags=0;
    tess_info.pNext=NULL;
    tess_info.patchControlPoints=tess_count;
}

void NormalPipeline::viewportInfo() {
    viewport.width=base->getWindowSize().width;
    viewport.height=base->getWindowSize().height;
    viewport.x=0;
    viewport.y=0;
    viewport.minDepth=-1.0f;
    viewport.maxDepth=1.0f;

    scissor.offset.x=0;
    scissor.offset.y=0;
    scissor.extent=base->getWindowSize();

    view_info.sType=VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
    view_info.viewportCount=1;
    view_info.pViewports=&viewport;
    view_info.scissorCount=1;
    view_info.pScissors=&scissor;
    view_info.flags=0;
    view_info.pNext=NULL;
}

void NormalPipeline::rasterize() {
    rast_info.sType=VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rast_info.cullMode=VK_CULL_MODE_BACK_BIT;
    rast_info.frontFace=VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rast_info.depthBiasEnable=VK_FALSE;
    rast_info.depthBiasClamp=0.0f;
    rast_info.depthBiasConstantFactor=0.0f;
    rast_info.depthBiasSlopeFactor=0.0f;
    rast_info.depthClampEnable=VK_TRUE;
    rast_info.flags=0;
    rast_info.pNext=NULL;
    rast_info.polygonMode=VK_POLYGON_MODE_FILL;
    rast_info.rasterizerDiscardEnable=VK_FALSE;
    rast_info.lineWidth=1.0f;
}

void NormalPipeline::multisample() {
    multi_info.sType=VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multi_info.alphaToCoverageEnable=VK_FALSE;
    multi_info.alphaToOneEnable=VK_FALSE;
    multi_info.flags=0;
    multi_info.minSampleShading=0.0f;
    multi_info.pSampleMask=NULL;
    multi_info.sampleShadingEnable=VK_FALSE;
    multi_info.rasterizationSamples=VK_SAMPLE_COUNT_1_BIT;
    multi_info.pNext=NULL;
}



void NormalPipeline::depthTesting() {
    depth_info.sType=VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depth_info.front={};
    depth_info.back={};
    depth_info.stencilTestEnable=VK_FALSE;
    depth_info.maxDepthBounds=1.0f;
    depth_info.minDepthBounds=-1.0f;
    depth_info.depthBoundsTestEnable=VK_TRUE;
    depth_info.depthCompareOp=VK_COMPARE_OP_LESS_OR_EQUAL;
    depth_info.depthTestEnable=VK_TRUE;
    depth_info.depthWriteEnable=VK_TRUE;
    depth_info.flags=0;
    depth_info.pNext=NULL;
}

void NormalPipeline::colorblend() {
    color_att.alphaBlendOp=VK_BLEND_OP_ADD;
    color_att.blendEnable=VK_TRUE;
    color_att.colorBlendOp=VK_BLEND_OP_ADD;
    color_att.colorWriteMask=15;
    color_att.srcAlphaBlendFactor=VK_BLEND_FACTOR_SRC_ALPHA;
    color_att.dstAlphaBlendFactor=VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    color_att.srcColorBlendFactor=VK_BLEND_FACTOR_SRC_COLOR;
    color_att.dstColorBlendFactor=VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;

    color_info.sType=VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    color_info.pNext=NULL;
    color_info.flags=0;
    color_info.attachmentCount=1;
    color_info.pAttachments=&color_att;
    color_info.logicOpEnable=VK_TRUE;
    color_info.logicOp=VK_LOGIC_OP_COPY;
    color_info.blendConstants[0]=0.0f;
    color_info.blendConstants[1]=0.0f;
    color_info.blendConstants[2]=0.0f;
    color_info.blendConstants[3]=0.0f;
}

void NormalPipeline::dynamicState() {
    dyn_info.sType=VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dyn_info.dynamicStateCount=0;
    dyn_info.pDynamicStates=NULL;
    dyn_info.flags=0;
    dyn_info.pNext=NULL;
}
