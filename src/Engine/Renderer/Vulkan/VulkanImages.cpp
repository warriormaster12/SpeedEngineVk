#include "Engine/Renderer/Vulkan/VulkanImages.h"

namespace Renderer
{
    void VulkanImages::initImages(VulkanDevices& vulkanDevices, VulkanMemoryAllocator& vulkanMemoryAllocator, AppWindow& win)
    {
        vulkanSwapChain.vulkanImageHandler.initImageHandler(vulkanDevices, vulkanMemoryAllocator);
        vulkanSwapChain.createSwapChain(win);
        vulkanSwapChain.createImageViews();
        vulkanRenderPass.initDepthBuffer(vulkanDevices, vulkanMemoryAllocator, vulkanSwapChain.vulkanImageHandler);
        vulkanRenderPass.createRenderPass(vulkanDevices.device, vulkanSwapChain.swapChainImageFormat);
        vulkanRenderPass.createDepthResources(vulkanSwapChain.swapChainExtent);
        vulkanFrameBuffer.createFramebuffers(vulkanDevices, vulkanSwapChain, vulkanRenderPass);
        
    }

    void VulkanImages::destroyImages(VulkanDevices& vulkanDevices)
    {
        vulkanRenderPass.destroyDepthBuffer();
        vulkanFrameBuffer.destroyFramebuffers(vulkanDevices);
        vulkanRenderPass.destroyRenderPass(vulkanDevices.device);
        vulkanSwapChain.destroySwapChain();
    }
}