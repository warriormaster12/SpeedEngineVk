#pragma once 

#include "../VkIncludes.h"
#include "../VkObjects.h"
#include "../VkGraphicsPipeline.h"
#include "../VkRenderPass.h"
#include "VkDepthBuffer.h"

namespace VkRenderer
{
    class VkframeBuffer
    {
    public: 
        std::vector<VkFramebuffer> swapChainFramebuffers;
        void createFramebuffers(VkMasterObject *vkobjects_ref, VkdepthBuffer *Dbuffer_ref,VkRenderpass *renderpass_ref);
    };
}