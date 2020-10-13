#include "Engine/Components/Mesh.h"

namespace VkRenderer
{

    void Mesh::InitMesh(VkSetup* setup, VkMemoryAllocator* memory_alloc, VkImageManager* image_m, VkCommandPool& commandPool)
    {
        DiffuseTexture.image_m_ref = image_m;
        NormalTexture.image_m_ref = image_m;
        DiffuseTexture.memory_alloc_ref = memory_alloc;
        NormalTexture.memory_alloc_ref = memory_alloc;

        indexBuffer_ref.setup_ref = setup_ref;
        indexBuffer_ref.memory_alloc_ref = memory_alloc;

        vertexBuffer_ref.setup_ref = setup;
        vertexBuffer_ref.memory_alloc_ref = memory_alloc;
        
        setup_ref = setup;

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