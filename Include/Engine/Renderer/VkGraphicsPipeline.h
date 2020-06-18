#pragma once 

#include "VkIncludes.h"
#include "VkShaderManager.h"
#include "Buffers/VkUnfiormbuffers.h"


namespace VkRenderer
{
    class VkGPipeline
    {
    public: 
        void createGraphicsPipeline(VkDevice& device, VkExtent2D& swapChainExtent, VkUbuffer& Ubuffer_ref);  
        void createRenderPass(VkDevice& device, VkFormat& swapChainImageFormat);
        
        VkPipelineLayout pipelineLayout;
        VkRenderPass renderPass;
        VkPipeline graphicsPipeline;

    private: 
        VkShader shader_ref;
    };
}