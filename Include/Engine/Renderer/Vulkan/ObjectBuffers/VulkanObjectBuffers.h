#pragma once 

#include "VulkanIndexBuffers.h"
#include "VulkanVertexBuffers.h"
#include "VulkanDescriptors.h"
#include "VulkanUniformBuffers.h"


namespace Renderer
{
    class VulkanObjectBuffers
    {
    public:
        VulkanIndexBuffer vulkanIndexBuffer;
        VulkanVertexBuffer vulkanVertexBuffer;
        VulkanDescriptors vulkanDescriptors;
        VulkanUniformBuffer vulkanUniformBuffer;
    };
}