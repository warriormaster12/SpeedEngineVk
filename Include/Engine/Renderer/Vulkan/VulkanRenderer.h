#pragma once 

#include "VulkanDevices.h"
#include "VulkanSwapChain.h"

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
        VulkanSwapChain vulkanSwapChain;
    };
    
}