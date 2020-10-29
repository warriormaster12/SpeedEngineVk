#pragma once

#include "../VulkanIncludes.h"
#include "../VulkanMemoryAllocator.h"

namespace Renderer
{
    

    class VulkanIndexBuffer
    {
    public: 
        VkBuffer indexBuffer;
        std::vector<uint32_t> indices;

        void createIndexBuffer(VulkanMemoryAllocator& vulkanMemoryAllocator);
        VmaAllocation allocation;
    };
}