#include "Engine/Renderer/Vulkan/VulkanImages.h"

namespace Renderer
{
    void VulkanImages::initImages(VulkanDevices& vulkanDevices, VulkanMemoryAllocator& vulkanMemoryAllocator, AppWindow& win)
    {
        vulkanImageHandler.initImageHandler(vulkanDevices, vulkanMemoryAllocator);
        createSwapChain(win);
        createImageViews();
        initDepthBuffer(vulkanDevices, vulkanMemoryAllocator, vulkanImageHandler);
        createRenderPass(vulkanDevices.device, swapChainImageFormat);
        createDepthResources(swapChainExtent);
    }

    void VulkanImages::destroyImages(VulkanDevices& vulkanDevices)
    {
        destroyDepthBuffer();
        destroyRenderPass(vulkanDevices.device);
        destroySwapChain();
    }
}