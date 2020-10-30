#pragma once 

#include "VulkanIncludes.h"
#include "ObjectBuffers/VulkanObjectBuffers.h"

namespace Renderer
{
 
    class VulkanModelLoader
    {
    public: 
        void loadModel(VulkanObjectBuffers& vulkanObjectBuffers, const std::string MODEL_PATH);
    };
}