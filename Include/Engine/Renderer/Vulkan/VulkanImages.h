#pragma once 

#include "VulkanSwapChain.h"
#include "VulkanDevices.h"
#include "VulkanRenderPass.h"
#include "VulkanMemoryAllocator.h"
#include "Buffers/VulkanFrameBuffer.h"
#include "../../Window/Window.h"

namespace Renderer
{
    class VulkanImages
    {
    public:
        void initImages(VulkanDevices& vulkanDevices, VulkanMemoryAllocator& vulkanMemoryAllocator, AppWindow& win);
        void destroyImages(VulkanDevices& vulkanDevices);     
    
        VulkanRenderPass vulkanRenderPass; 
        VulkanSwapChain vulkanSwapChain;
        VulkanFrameBuffer vulkanFrameBuffer;
    };
}