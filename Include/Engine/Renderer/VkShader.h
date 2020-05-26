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
    class VkShader
    {
    public: 
        static std::vector<char> readFile(const std::string& filename);
        VkShaderModule createShaderModule(VkDevice device,const std::vector<char>& code);
    };
}