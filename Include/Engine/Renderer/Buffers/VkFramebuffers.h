#pragma once 

#include "../VkIncludes.h"
#include "../VkSetup.h"
#include "../VkGraphicsPipeline.h"
#include "../VkRenderPass.h"
#include "../VkSwapChain.h"
#include "VkDepthBuffer.h"

namespace VkRenderer
{
    class VkframeBuffer
    {
    public: 
        std::vector<VkFramebuffer> swapChainFramebuffers;
        void createFramebuffers();

        VkSetup *setup_ref;
        VkSwapChain *swap_ref;
        VkGPipeline *gpipeline_ref;
        VkRenderpass *renderpass_ref;
        VkdepthBuffer *Dbuffer_ref;
    };
}