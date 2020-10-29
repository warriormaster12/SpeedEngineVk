#pragma once 

#include "VulkanDevices.h"
#include "VulkanImages.h"
#include "VulkanMemoryAllocator.h"
#include "VulkanGraphicsPipeline.h"
#include "ObjectBuffers/VulkanObjectBuffers.h"

namespace Renderer
{
    class Vulkan
    {
    public: 
        void initVulkan(AppWindow& win);
        void updateVulkan(double deltaTime);
        void destroyVulkan();
    private: 
        VulkanDevices vulkanDevices;
        VulkanImages vulkanImages;
        VulkanObjectBuffers vulkanObjectBuffers;
        VulkanGraphicsPipeline vulkanGraphicsPipeline;
        VulkanMemoryAllocator vulkanMemoryAllocator;
    };
    
}