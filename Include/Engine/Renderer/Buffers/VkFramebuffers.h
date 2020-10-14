#pragma once 

#include "../VkIncludes.h"
#include "../VkSetup.h"
#include "../VkSwapChain.h"
#include "../VkGraphicsPipeline.h"
#include "../VkRenderPass.h"
#include "VkDepthBuffer.h"

namespace VkRenderer
{
    class VkframeBuffer
    {
    public: 
        std::vector<VkFramebuffer> swapChainFramebuffers;
        void createFramebuffers(VkSetup *setup_ref, VkSwapChain *swap_ref, VkdepthBuffer *Dbuffer_ref,VkRenderpass *renderpass_ref);
    };
}