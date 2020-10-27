#pragma once 

#include "VulkanDevices.h"
#include "VulkanImages.h"
#include "VulkanMemoryAllocator.h"

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
        VulkanMemoryAllocator vulkanMemoryAllocator;
    };
    
}