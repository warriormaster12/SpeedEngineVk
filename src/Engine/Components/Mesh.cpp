#include "Engine/Components/Mesh.h"

namespace Renderer
{
    void Mesh::initMesh(Vulkan& vulkan_api)
    {
        p_vulkan_api = &vulkan_api;

        p_vulkan_api->vulkanObjectBuffers.vulkanDescriptors.createDescriptorSetLayout(p_vulkan_api->vulkanDevices, p_vulkan_api->vulkanImages.vulkanSwapChain.swapChainImages.size());
        p_vulkan_api->vulkanGraphicsPipeline.vertex_attributes = vertex_attributes;
        p_vulkan_api->vulkanGraphicsPipeline.shaders = shaders;
        p_vulkan_api->vulkanGraphicsPipeline.createGraphicsPipeline(p_vulkan_api->vulkanDevices, p_vulkan_api->vulkanImages, p_vulkan_api->vulkanObjectBuffers.vulkanDescriptors.descriptorSetLayout);

        p_vulkan_api->vulkanModelLoader.loadModel(p_vulkan_api->vulkanObjectBuffers, model_path);
        p_vulkan_api->vulkanObjectBuffers.vulkanVertexBuffer.createVertexBuffer(p_vulkan_api->vulkanMemoryAllocator);
        p_vulkan_api->vulkanObjectBuffers.vulkanIndexBuffer.createIndexBuffer(p_vulkan_api->vulkanMemoryAllocator);
        
        p_vulkan_api->vulkanObjectBuffers.vulkanDescriptors.createDescriptorPool();
        p_vulkan_api->vulkanObjectBuffers.vulkanDescriptors.createDescriptorSets();
        p_vulkan_api->vulkanCommandBuffer.createCommandPool(p_vulkan_api->vulkanDevices, p_vulkan_api->vulkanImages);
        p_vulkan_api->vulkanCommandBuffer.createCommandBuffers(p_vulkan_api->vulkanObjectBuffers.vulkanDescriptors.descriptorSets);
    }
}