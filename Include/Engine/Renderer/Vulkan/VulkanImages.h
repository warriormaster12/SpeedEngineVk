#pragma once 

#include "VulkanSwapChain.h"
#include "VulkanDevices.h"
#include "VulkanMemoryAllocator.h"
#include "../../Window/Window.h"

namespace Renderer
{
    class VulkanImages : public VulkanSwapChain
    {
    public:
        void initImages(VulkanDevices& vulkanDevices, VulkanMemoryAllocator& vulkanMemoryAllocator, AppWindow& win);
        void destroyImages();        
    };
}