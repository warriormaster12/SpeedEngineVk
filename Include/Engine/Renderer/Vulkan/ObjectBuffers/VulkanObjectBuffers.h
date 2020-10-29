#pragma once 

#include "VulkanIndexBuffers.h"
#include "VulkanVertexBuffers.h"
#include "VulkanDescriptors.h"


namespace Renderer
{
    class VulkanObjectBuffers
    {
    public:
        VulkanIndexBuffer vulkanIndexBuffer;
        VulkanVertexBuffer vulkanVertexBuffer;
        VulkanDescriptors vulkanDescriptors;
    };
}