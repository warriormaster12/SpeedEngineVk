#pragma once 

#include "VulkanIncludes.h"
#include "ShaderCompiler/VulkanShaderManager.h"
#include "VulkanDevices.h"
#include "VulkanImages.h"



namespace Renderer
{
    struct PushConstants
    {
        bool Unlit;
        int light_count;
    };
    class VulkanGraphicsPipeline
    {
    public: 
        void createGraphicsPipeline(VulkanDevices& vulkanDevices, VulkanImages& vulkanImages, VkDescriptorSetLayout descriptorSetLayout);  
        void destroyPipeline(VulkanDevices& vulkanDevices);
        
        std::vector <std::string> shaders;
        size_t vertex_attributes = 4;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;
        

    private: 
        VulkanShaderManager vulkanShaderManager;

        VkPipelineShaderStageCreateInfo loadShader(VkShaderModule module,VkShaderStageFlagBits stage);
        inline VkPushConstantRange pushConstantRange(VkShaderStageFlags stageFlags,uint32_t size,uint32_t offset);
    };
}