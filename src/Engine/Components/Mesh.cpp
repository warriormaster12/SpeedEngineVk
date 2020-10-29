#include "Engine/Components/Mesh.h"

namespace Renderer
{
    void Mesh::initMesh(Vulkan& vulkan_api)
    {
        p_vulkan_api = &vulkan_api;

        p_vulkan_api->vulkanObjectBuffers.vulkanDescriptors.createDescriptorSetLayout(p_vulkan_api->vulkanDevices);
        p_vulkan_api->vulkanGraphicsPipeline.vertex_attributes = vertex_attributes;
        p_vulkan_api->vulkanGraphicsPipeline.shaders = shaders;
        p_vulkan_api->vulkanGraphicsPipeline.createGraphicsPipeline(p_vulkan_api->vulkanDevices, p_vulkan_api->vulkanImages, p_vulkan_api->vulkanObjectBuffers.vulkanDescriptors.descriptorSetLayout);
    }
}