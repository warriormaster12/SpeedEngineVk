#pragma once 

#include "VkIncludes.h"

namespace VkRenderer
{
    class VkShader
    {
    public: 
        static std::vector<char> readFile(const std::string& filename);
        VkShaderModule createShaderModule(VkDevice device,const std::vector<char>& code);
    };
}