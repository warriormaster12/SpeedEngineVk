#include "Engine/Renderer/Vulkan/VulkanRenderer.h"

namespace Renderer
{
    void Vulkan::initVulkan(AppWindow& win)
    {
        vulkanDevices.initializeDevices();
        vulkanImages.initializeSwapChain(vulkanDevices, win);
        vulkanDevices.createLogicalDevice(vulkanImages.surface);
        vulkanMemoryAllocator.createAllocator(vulkanDevices);
        vulkanImages.initImages(vulkanDevices, vulkanMemoryAllocator, win);
        
        
    }

    void Vulkan::updateVulkan(double deltaTime)
    {

    }

    void Vulkan::destroyVulkan()
    {
        vulkanImages.destroyImages();
        vulkanMemoryAllocator.destroyAllocator();
        vulkanDevices.destroyDevices();
    }
}