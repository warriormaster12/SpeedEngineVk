#pragma once 
#include "../Renderer/VkIncludes.h"
#include "../Renderer/VkModelLoader.h"
#include "../Renderer/VkSetup.h"
#include "../Renderer/Buffers/VkVertexbuffers.h"
#include "../Renderer/Buffers/VkIndexbuffers.h"






namespace VkRenderer
{
    struct Transform3D
    {
        glm::vec3 translate;
        glm::vec3 scale;
    };
    class Mesh 
    {
    public: 
        ModelLoader model_ref;
        VkVbuffer Vbuffer_ref;
        VkindexBuffer Ibuffer_ref;  

        
        VkSetup *setup_ref;
        
        Transform3D mesh_transform;
        
        

        void InitMesh(VkCommandPool& commandPool);
        void update(uint32_t imageIndex);
        void DestroyMesh();
    };

}