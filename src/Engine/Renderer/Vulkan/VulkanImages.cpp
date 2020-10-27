#include "Engine/Renderer/Vulkan/VulkanImages.h"

namespace Renderer
{
    void VulkanImages::initImages(VulkanDevices& vulkanDevices, VulkanMemoryAllocator& vulkanMemoryAllocator, AppWindow& win)
    {
        vulkanImageHandler.initImageHandler(vulkanDevices, vulkanMemoryAllocator);
        createSwapChain(win);
        createImageViews();
    }

    void VulkanImages::destroyImages()
    {
        destroySwapChain();
    }
}