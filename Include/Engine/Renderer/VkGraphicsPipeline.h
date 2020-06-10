#pragma once 

#include "VkIncludes.h"
#include "VkShaderManager.h"

namespace VkRenderer
{
    class VkGPipeline
    {
    public: 
        void createGraphicsPipeline(VkDevice& device, VkExtent2D& swapChainExtent);  
        void createRenderPass(VkDevice& device, VkFormat& swapChainImageFormat);
        
        VkPipelineLayout pipelineLayout;
        VkRenderPass renderPass;
        VkPipeline graphicsPipeline;
    private: 
        VkShader shader_ref;
    };
}