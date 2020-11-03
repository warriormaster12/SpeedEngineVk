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
        std::vector <VkBuffer> createBuffer(uint32_t byte_size, uint32_t size);
        void updateBuffer(uint32_t imageIndex, const void *__restrict object, uint32_t byte_size);
        void destroyBuffer();
        std::vector <VmaAllocation> bufferAllocation;
        std::vector<VkBuffer> Buffers;
    private:
        VulkanMemoryAllocator* p_vulkanMemoryAllocator;
    };
}