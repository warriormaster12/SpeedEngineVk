#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
#include <chrono>

namespace VkRenderer
{
    class VkShader
    {
    public: 
        static std::vector<char> readFile(const std::string& filename);
        VkShaderModule createShaderModule(VkDevice device,const std::vector<char>& code);
    };
}