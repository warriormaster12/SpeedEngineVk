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

        p_vulkan_api->vulkanObjectBuffers.vulkanUniformBuffer.initBuffer(p_vulkan_api->vulkanMemoryAllocator);
        p_vulkan_api->vulkanObjectBuffers.vulkanDescriptors.createDescriptorPool();
        p_vulkan_api->vulkanObjectBuffers.vulkanDescriptors.createDescriptorSets(p_vulkan_api->vulkanObjectBuffers.vulkanUniformBuffer.createBuffer(sizeof(UniformBufferObject), p_vulkan_api->vulkanImages.vulkanSwapChain.swapChainImages.size()), sizeof(UniformBufferObject));
        
        p_vulkan_api->vulkanCommandBuffer.createCommandPool(p_vulkan_api->vulkanDevices, p_vulkan_api->vulkanImages);
        p_vulkan_api->vulkanCommandBuffer.createCommandBuffers(p_vulkan_api->vulkanObjectBuffers, p_vulkan_api->vulkanGraphicsPipeline);
        p_vulkan_api->createSyncObjects();
    }

    const void *__restrict Mesh::drawMesh(double deltaTime)
    {
        
        glm::mat4 ModelMatrix(1.0f);
        ubo.model = ModelMatrix;

        float aspect = p_vulkan_api->vulkanImages.vulkanSwapChain.swapChainExtent.width / (float) p_vulkan_api->vulkanImages.vulkanSwapChain.swapChainExtent.height;

        transform.scale = glm::vec3(0.2f);

        ubo.model = glm::translate(ubo.model, transform.translate);
        ubo.model = glm::rotate(ubo.model, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        ubo.model= glm::rotate(ubo.model, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        ubo.model= glm::rotate(ubo.model, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.model = glm::scale(ubo.model, transform.scale);	

        camera.CameraUpdate(deltaTime);
        ubo.view = camera.matrices.view;
        ubo.projection = camera.matrices.perspective;

        return &ubo;
    }

    void Mesh::destroyMesh()
    {
        p_vulkan_api->vulkanGraphicsPipeline.destroyPipeline(p_vulkan_api->vulkanDevices);
        p_vulkan_api->vulkanObjectBuffers.vulkanUniformBuffer.destroyBuffer();
        p_vulkan_api->vulkanObjectBuffers.vulkanVertexBuffer.destroyVertexBuffer(p_vulkan_api->vulkanMemoryAllocator);
        p_vulkan_api->vulkanObjectBuffers.vulkanIndexBuffer.destroyIndexBuffer(p_vulkan_api->vulkanMemoryAllocator);

        vkFreeCommandBuffers(p_vulkan_api->vulkanDevices.device, p_vulkan_api->vulkanCommandBuffer.commandPool, static_cast<uint32_t>(p_vulkan_api->vulkanCommandBuffer.commandBuffers.size()), p_vulkan_api->vulkanCommandBuffer.commandBuffers.data());
        vkDestroyCommandPool(p_vulkan_api->vulkanDevices.device, p_vulkan_api->vulkanCommandBuffer.commandPool, nullptr);
        vkDestroyDescriptorPool(p_vulkan_api->vulkanDevices.device, p_vulkan_api->vulkanObjectBuffers.vulkanDescriptors.descriptorPool, nullptr);
        vkDestroyDescriptorSetLayout(p_vulkan_api->vulkanDevices.device, p_vulkan_api->vulkanObjectBuffers.vulkanDescriptors.descriptorSetLayout, nullptr);  
        
    }
}