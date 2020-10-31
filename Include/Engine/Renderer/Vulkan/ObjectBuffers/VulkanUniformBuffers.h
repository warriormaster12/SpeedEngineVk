#pragma once 

#include "../VulkanIncludes.h"
#include "../VulkanDevices.h"
#include "../VulkanMemoryAllocator.h"

namespace Renderer
{
    class VulkanUniformBuffer
    {
    public: 
        void initBuffer(VulkanMemoryAllocator& vulkanMemoryAllocator);
        std::vector <VkBuffer> createBuffer(std::vector <VkBuffer> inputBuffer, uint32_t byte_size, uint32_t size);
        std::vector <VmaAllocation> bufferAllocation;
    private:
        VulkanMemoryAllocator* p_vulkanMemoryAllocator;
    };
}