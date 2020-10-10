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
        vertexBuffer_ref.createVertexBuffer();
        indexBuffer_ref.createIndexBuffer();
        
    }


    void Mesh::DestroyMesh()
    {
        DiffuseTexture.DestroyTexture();
        NormalTexture.DestroyTexture();

        vmaDestroyBuffer(indexBuffer_ref.memory_alloc_ref->allocator, indexBuffer_ref.indexBuffer, indexBuffer_ref.allocation);

        vmaDestroyBuffer(vertexBuffer_ref.memory_alloc_ref->allocator, vertexBuffer_ref.vertexBuffer, vertexBuffer_ref.allocation);
    }
}