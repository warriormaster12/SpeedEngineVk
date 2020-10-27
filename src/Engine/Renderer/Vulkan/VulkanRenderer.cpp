#include "Engine/Renderer/Vulkan/VulkanRenderer.h"

namespace Renderer
{
    void Vulkan::initVulkan(AppWindow& win)
    {
        vulkanDevices.initializeDevices();
        vulkanSwapChain.initializeSwapChain(vulkanDevices, win);
        vulkanDevices.createLogicalDevice(vulkanSwapChain.surface);
        vulkanSwapChain.createSwapChain(win);
        vulkanSwapChain.createImageViews();
    }

    void Vulkan::updateVulkan(double deltaTime)
    {

    }

    void Vulkan::destroyVulkan()
    {
        vulkanSwapChain.destroySwapChain();
        vulkanDevices.destroyDevices();
    }
}