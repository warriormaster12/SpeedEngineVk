#include "Engine/Components/Mesh.h"

namespace VkRenderer
{
    Mesh::Mesh()
    {
        model_ref.Ibuffer_ref = &Ibuffer_ref;
        model_ref.Vbuffer_ref = &Vbuffer_ref;
    }

    void Mesh::InitMesh(VkCommandPool& commandPool)
    {
        mesh_transform.translate = glm::vec3(0.0f,0.0f,0.0f);
        mesh_transform.scale = glm::vec3(1.0f,1.0f,1.0f);

        texture_m_ref.createTextureImage(model_ref.TEXTURE_PATH, commandPool);
        texture_m_ref.createTextureImageView();
        texture_m_ref.createTextureSampler();
        model_ref.loadModel();
        Vbuffer_ref.createVertexBuffer(commandPool);
        Ibuffer_ref.createIndexBuffer(commandPool);
        Ubuffer_ref.createUniformBuffers(swap_ref->swapChainImages); 
        Ubuffer_ref.createDescriptorPool(swap_ref->swapChainImages);
        Ubuffer_ref.createDescriptorSets(swap_ref->swapChainImages, texture_m_ref.textureImageView,  texture_m_ref.textureSampler);
    }

    void Mesh::update(uint32_t imageIndex)
    {
        Ubuffer_ref.transform.translate = mesh_transform.translate;
        Ubuffer_ref.transform.scale = mesh_transform.scale;

        Ubuffer_ref.updateUniformBuffer(imageIndex, swap_ref->swapChainExtent);
    }

    void Mesh::DestroyMesh()
    {
        vkDestroySampler(setup_ref->device, texture_m_ref.textureSampler, nullptr);
        vkDestroyImageView(setup_ref->device, texture_m_ref.textureImageView, nullptr);

        vkDestroyImage(setup_ref->device, texture_m_ref.textureImage, nullptr);
        vkFreeMemory(setup_ref->device, texture_m_ref.textureImageMemory, nullptr);

        vkDestroyDescriptorSetLayout(setup_ref->device, Ubuffer_ref.descriptorSetLayout, nullptr);

        vkDestroyBuffer(setup_ref->device, Ibuffer_ref.indexBuffer, nullptr);
        vkFreeMemory(setup_ref->device, Ibuffer_ref.indexBufferMemory, nullptr);

        vkDestroyBuffer(setup_ref->device, Vbuffer_ref.vertexBuffer, nullptr);
        vkFreeMemory(setup_ref->device, Vbuffer_ref.vertexBufferMemory, nullptr);
    }
}