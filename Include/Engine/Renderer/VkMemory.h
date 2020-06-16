#pragma once 
#include "VkIncludes.h"

namespace VkRenderer
{
    class VkMemory
    {
    public: 
        VkMemoryRequirements memRequirements;
        VkDeviceMemory indexBufferMemory;
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice& physicalDevice);
    };
}