#pragma once 

#include "VkIncludes.h"
#include "VkShaderManager.h"
#include "VkSetup.h"
#include "Buffers/VkUnfiormbuffers.h"


namespace VkRenderer
{
    class VkGPipeline
    {
    public: 
        void createGraphicsPipeline(VkExtent2D& swapChainExtent);  
        void createRenderPass(VkFormat& swapChainImageFormat);
        
        VkPipelineLayout pipelineLayout;
        VkRenderPass renderPass;
        VkPipeline graphicsPipeline;

        VkSetup *setup_ref;
        VkUbuffer *Ubuffer_ref;

    private: 
        VkShader shader_ref;
    };
}