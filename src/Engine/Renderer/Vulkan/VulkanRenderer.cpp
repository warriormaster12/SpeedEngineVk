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
        vulkanGraphicsPipeline.shaders = {"EngineAssets/Shaders/light_cube_vert.vert","EngineAssets/Shaders/light_cube_frag.frag"};
        vulkanGraphicsPipeline.createGraphicsPipeline(vulkanDevices, vulkanImages, nullptr);
        
    }

    void Vulkan::updateVulkan(double deltaTime)
    {

    }

    void Vulkan::destroyVulkan()
    {
        vulkanGraphicsPipeline.destroyPipeline(vulkanDevices);
        vulkanImages.destroyImages(vulkanDevices);
        vulkanMemoryAllocator.destroyAllocator();
        vulkanDevices.destroyDevices();
    }
}