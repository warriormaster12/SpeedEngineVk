#pragma once 
#include "VkIncludes.h"

namespace VkRenderer
{
    class VkTextureManager
    {
    public: 
        void createTextureSampler(VkDevice device);
        VkSampler textureSampler; 
    };
}