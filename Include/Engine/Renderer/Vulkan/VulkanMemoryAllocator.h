#pragma once 

#include "../../Vma/vk_mem_alloc.h"
#include "VulkanIncludes.h"
#include "VulkanDevices.h"

namespace Renderer
{
    class VulkanMemoryAllocator
    {
    public: 
        VmaAllocator allocator; 
        void createAllocator(VulkanDevices& vulkanDevices);
        void destroyAllocator();
    };
}
