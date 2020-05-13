#pragma once 

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <optional>
#include <set>
#include <algorithm>
#include <fstream>
#include <array>

namespace VkRenderer
{
    class VkMemory
    {
    public: 
        VkMemoryRequirements memRequirements;
        VkDeviceMemory vertexBufferMemory;
        VkDeviceMemory indexBufferMemory;
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physicalDevice);
    };
}