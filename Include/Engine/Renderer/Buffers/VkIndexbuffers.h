#pragma once

#include "../VkIncludes.h"
#include "../VkSetup.h"
#include "../VkMemoryAllocator.h"

namespace VkRenderer
{
    

    class VkindexBuffer
    {
    public: 
        VkBuffer indexBuffer;
        std::vector<uint32_t> indices;

        void createIndexBuffer();

        VkSetup *setup_ref;
        VkMemoryAllocator *memory_alloc_ref;
        VmaAllocation allocation;
    };
}