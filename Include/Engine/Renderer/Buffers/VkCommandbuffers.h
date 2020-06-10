#pragma once 

#include "../VkIncludes.h"
#include "../VkSetup.h"
#include "../VkGraphicsPipeline.h"

namespace VkRenderer
{
    class VkcommandBuffer
    {
    public: 
        VkCommandPool commandPool;
        void createCommandPool(VkSetup& setup_ref, VkSurfaceKHR& surface);
        void createCommandBuffers(VkDevice& device, std::vector<VkFramebuffer> swapChainFramebuffers, VkExtent2D& swapChainExtent, VkGPipeline& Gpipeline_ref);
        std::vector<VkCommandBuffer> commandBuffers;
    };
}