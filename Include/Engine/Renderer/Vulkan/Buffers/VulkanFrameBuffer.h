#pragma once 

#include "../VulkanIncludes.h"
#include "../VulkanDevices.h"
#include "../VulkanSwapChain.h"
#include "../VulkanRenderPass.h"


namespace Renderer
{
    class VulkanFrameBuffer
    {
    public: 
        std::vector<VkFramebuffer> swapChainFramebuffers;
        void createFramebuffers(VulkanDevices& vulkanDevices, VulkanSwapChain& vulkanSwapChain, VulkanRenderPass& vulkanRenderPass);
        void destroyFramebuffers(VulkanDevices& vulkanDevices);
    };
}