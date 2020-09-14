#include "Engine/Components/Mesh.h"

namespace VkRenderer
{

    void Mesh::InitMesh(VkCommandPool& commandPool)
    {
        DiffuseTexture.BindTexture(commandPool);
        NormalTexture.BindTexture(commandPool);

        model_ref.indexBuffer_ref = &indexBuffer_ref;
        model_ref.vertexBuffer_ref = &vertexBuffer_ref;

        mesh_transform.translate = glm::vec3(0.0f,0.0f,0.0f);
        mesh_transform.scale = glm::vec3(1.0f,1.0f,1.0f);

        
        model_ref.loadModel();
        vertexBuffer_ref.createVertexBuffer(commandPool);
        indexBuffer_ref.createIndexBuffer(commandPool);
        
    }


    void Mesh::DestroyMesh()
    {
        DiffuseTexture.DestroyTexture();
        NormalTexture.DestroyTexture();

        vkDestroyBuffer(setup_ref->device, indexBuffer_ref.indexBuffer, nullptr);
        vkFreeMemory(setup_ref->device, indexBuffer_ref.indexBufferMemory, nullptr);

        vkDestroyBuffer(setup_ref->device, vertexBuffer_ref.vertexBuffer, nullptr);
        vkFreeMemory(setup_ref->device, vertexBuffer_ref.vertexBufferMemory, nullptr);
    }
}