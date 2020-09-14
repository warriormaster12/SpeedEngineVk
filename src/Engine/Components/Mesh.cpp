#include "Engine/Components/Mesh.h"

namespace VkRenderer
{
    void Mesh::BindTexture(VkCommandPool& commandPool)
    {
        texture.setup_ref = setup_ref;
        texture.buffer_ref = buffer_ref;
        texture.memory_ref = memory_ref;

        texture.createTextureImage(TEXTURE_PATH, commandPool);
        texture.createTextureImageView();
        texture.createTextureSampler();
    }

    void Mesh::InitMesh(VkCommandPool& commandPool)
    {
        model_ref.indexBuffer_ref = &indexBuffer_ref;
        model_ref.vertexBuffer_ref = &vertexBuffer_ref;

        mesh_transform.translate = glm::vec3(0.0f,0.0f,0.0f);
        mesh_transform.scale = glm::vec3(1.0f,1.0f,1.0f);

        
        model_ref.loadModel();
        vertexBuffer_ref.createVertexBuffer(commandPool);
        indexBuffer_ref.createIndexBuffer(commandPool);
        
    }

    void Mesh::DestroyTexture()
    {
        vkDestroySampler(setup_ref->device, texture.textureSampler, nullptr);
        vkDestroyImageView(setup_ref->device, texture.textureImageView, nullptr);
        
        vkDestroyImage(setup_ref->device, texture.textureImage, nullptr);
        vkFreeMemory(setup_ref->device, texture.textureImageMemory, nullptr);
    }


    void Mesh::DestroyMesh()
    {

        vkDestroyBuffer(setup_ref->device, indexBuffer_ref.indexBuffer, nullptr);
        vkFreeMemory(setup_ref->device, indexBuffer_ref.indexBufferMemory, nullptr);

        vkDestroyBuffer(setup_ref->device, vertexBuffer_ref.vertexBuffer, nullptr);
        vkFreeMemory(setup_ref->device, vertexBuffer_ref.vertexBufferMemory, nullptr);
    }
}