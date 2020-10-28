#pragma once 

#include "VulkanIncludes.h"
#include "Buffers/VulkanDepthBuffer.h"




namespace Renderer
{
    class VulkanRenderPass : public VulkanDepthBuffer
    {
    public: 
        void createRenderPass(VkDevice& device, VkFormat& swapChainImageFormat);
        void destroyRenderPass(VkDevice& device);
        VkRenderPass renderPass;
    };
}