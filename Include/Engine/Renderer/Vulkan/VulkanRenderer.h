#pragma once 

#include "VulkanDevices.h"

namespace Renderer
{
    class Vulkan
    {
    public: 
        void initVulkan();
        void updateVulkan(double deltaTime);
        void destroyVulkan();
    private: 
        VulkanDevices vulkanDevices;
    };
    
}