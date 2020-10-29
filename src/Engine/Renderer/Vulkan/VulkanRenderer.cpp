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

        //Per shader process
        vulkanObjectBuffers.vulkanDescriptors.createDescriptorSetLayout(vulkanDevices);
        vulkanGraphicsPipeline.vertex_attributes = 1;
        vulkanGraphicsPipeline.shaders = {"EngineAssets/Shaders/light_cube_vert.vert","EngineAssets/Shaders/light_cube_frag.frag"};
        vulkanGraphicsPipeline.createGraphicsPipeline(vulkanDevices, vulkanImages, vulkanObjectBuffers.vulkanDescriptors.descriptorSetLayout);
        
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