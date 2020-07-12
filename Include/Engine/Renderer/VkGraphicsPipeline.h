#pragma once 

#include "VkIncludes.h"
#include "VkShaderManager.h"
#include "VkSetup.h"
#include "VkSwapChain.h"
#include "Buffers/VkUnfiormbuffers.h"


namespace VkRenderer
{
    class VkGPipeline
    {
    public: 
        void createGraphicsPipeline();  
        void createRenderPass();
        
        VkPipelineLayout pipelineLayout;
        VkRenderPass renderPass;
        VkPipeline graphicsPipeline;

        VkSetup *setup_ref;
        VkSwapChain *swap_ref;
        VkUbuffer *Ubuffer_ref;

    private: 
        VkShader shader_ref;
    };
}