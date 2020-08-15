#include "Engine/Components/Mesh.h"

namespace VkRenderer
{


    void Mesh::InitMesh(VkCommandPool& commandPool)
    {
        model_ref.Ibuffer_ref = &Ibuffer_ref;
        model_ref.Vbuffer_ref = &Vbuffer_ref;

        mesh_transform.translate = glm::vec3(0.0f,0.0f,0.0f);
        mesh_transform.scale = glm::vec3(1.0f,1.0f,1.0f);

        
        model_ref.loadModel();
        Vbuffer_ref.createVertexBuffer(commandPool);
        Ibuffer_ref.createIndexBuffer(commandPool);
        
    }


    void Mesh::DestroyMesh()
    {

        vkDestroyBuffer(setup_ref->device, Ibuffer_ref.indexBuffer, nullptr);
        vkFreeMemory(setup_ref->device, Ibuffer_ref.indexBufferMemory, nullptr);

        vkDestroyBuffer(setup_ref->device, Vbuffer_ref.vertexBuffer, nullptr);
        vkFreeMemory(setup_ref->device, Vbuffer_ref.vertexBufferMemory, nullptr);
    }
}