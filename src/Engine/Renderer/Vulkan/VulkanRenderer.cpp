#include "Engine/Renderer/Vulkan/VulkanRenderer.h"

namespace Renderer
{
    void Vulkan::initVulkan(AppWindow& win)
    {
        vulkanDevices.initializeDevices();
        vulkanImages.vulkanSwapChain.initializeSwapChain(vulkanDevices, win);
        vulkanDevices.createLogicalDevice(vulkanImages.vulkanSwapChain.surface);
        vulkanMemoryAllocator.createAllocator(vulkanDevices);
        vulkanImages.initImages(vulkanDevices, vulkanMemoryAllocator, win);
        
        
    }

    void Vulkan::updateVulkan(double deltaTime)
    {

    }

    void Vulkan::destroyVulkan()
    {
        vulkanImages.destroyImages(vulkanDevices);
        vulkanMemoryAllocator.destroyAllocator();
        vulkanDevices.destroyDevices();
    }
}