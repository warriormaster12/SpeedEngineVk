#include "Engine/Components/Mesh.h"

namespace VkRenderer
{

    void Mesh::InitMesh(VkSetup* setup, VkMemoryAllocator* memory_alloc, VkImageManager* image_m, VkCommandPool& commandPool)
    {
        DiffuseTexture.image_m_ref = image_m;
        NormalTexture.image_m_ref = image_m;
        DiffuseTexture.memory_alloc_ref = memory_alloc;
        NormalTexture.memory_alloc_ref = memory_alloc;
        cube_map.image_m_ref = image_m;
        cube_map.memory_alloc_ref = memory_alloc;

        indexBuffer.setup_ref = setup_ref;
        indexBuffer.memory_alloc_ref = memory_alloc;

        vertexBuffer.setup_ref = setup;
        vertexBuffer.memory_alloc_ref = memory_alloc;
        
        setup_ref = setup;

        DiffuseTexture.BindTexture(commandPool);
        NormalTexture.BindTexture(commandPool);
        //cube_map.BindTexture(commandPool);

        model.indexBuffer_ref = &indexBuffer;
        model.vertexBuffer_ref = &vertexBuffer;

        mesh_transform.translate = glm::vec3(0.0f,0.0f,0.0f);
        mesh_transform.scale = glm::vec3(1.0f,1.0f,1.0f);

        
        model.loadModel();
        vertexBuffer.createVertexBuffer();
        indexBuffer.createIndexBuffer();
        
    }


    void Mesh::DestroyMesh()
    {
        DiffuseTexture.DestroyTexture();
        NormalTexture.DestroyTexture();

        vmaDestroyBuffer(indexBuffer.memory_alloc_ref->allocator, indexBuffer.indexBuffer, indexBuffer.allocation);

        vmaDestroyBuffer(vertexBuffer.memory_alloc_ref->allocator, vertexBuffer.vertexBuffer, vertexBuffer.allocation);
    }
}