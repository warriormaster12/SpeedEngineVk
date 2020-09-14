#pragma once 

#include "VkIncludes.h"
#include "VkShaderManager.h"
#include "VkSetup.h"
#include "Buffers/VkDepthBuffer.h"
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
        VkuniformBuffer *uniformBuffer_ref;
        VkdepthBuffer *Dbuffer_ref;

    private: 
        VkShader shader_ref;
    };
}