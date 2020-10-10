#pragma once 

#include "../Vma/vk_mem_alloc.h"
#include "VkIncludes.h"
#include "VkSetup.h"


class VkMemoryAllocator
{
public: 
    VmaAllocator allocator; 
    void createAllocator(VkRenderer::VkSetup& setup_ref);
};