#include "Engine/Renderer/Vulkan/VulkanRenderer.h"

namespace Renderer
{
    void Vulkan::initVulkan()
    {
        vulkanDevices.InitializeDevices();
    }

    void Vulkan::updateVulkan(double deltaTime)
    {

    }

    void Vulkan::destroyVulkan()
    {
        vulkanDevices.destroyDevices();
    }
}