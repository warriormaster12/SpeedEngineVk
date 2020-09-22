#pragma once 

#include "VkIncludes.h"
#include "VkShaderManager.h"
#include "VkSetup.h"
#include "Buffers/VkDepthBuffer.h"



namespace VkRenderer
{
    struct PushConstants
    {
        bool Unlit;
        int light_count;
    };
    class VkGPipeline
    {
    public: 
        void createGraphicsPipeline(VkExtent2D& swapChainExtent, VkDescriptorSetLayout descriptorSetLayout);  
        void createRenderPass(VkFormat& swapChainImageFormat);
        
        VkPipelineLayout pipelineLayout;
        VkRenderPass renderPass;
        VkPipeline graphicsPipeline;

        VkSetup *setup_ref;
        VkdepthBuffer *Dbuffer_ref;

    private: 
        VkShader shader_ref;

        VkPipelineShaderStageCreateInfo loadShader(VkShaderModule module,VkShaderStageFlagBits stage);
        inline VkPushConstantRange pushConstantRange(VkShaderStageFlags stageFlags,uint32_t size,uint32_t offset);
    };
}