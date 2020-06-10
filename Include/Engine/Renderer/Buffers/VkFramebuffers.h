#pragma once 

#include "../VkIncludes.h"

namespace VkRenderer
{
    class VkframeBuffer
    {
    public: 
        std::vector<VkFramebuffer> swapChainFramebuffers;
        void createFramebuffers(VkDevice& device, std::vector<VkImageView> swapChainImageViews, VkExtent2D& swapChainExtent, VkRenderPass& renderPass);
    };
}