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
        void createGraphicsPipeline(VkExtent2D& swapChainExtent, VkRenderPass& renderPass,VkDescriptorSetLayout descriptorSetLayout);  
        
        std::vector <std::string> shaders;
        size_t vertex_attributes = 4;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;
        VkSetup *setup_ref;
        

    private: 
        VkShader shader_ref;

        VkPipelineShaderStageCreateInfo loadShader(VkShaderModule module,VkShaderStageFlagBits stage);
        inline VkPushConstantRange pushConstantRange(VkShaderStageFlags stageFlags,uint32_t size,uint32_t offset);
    };
}