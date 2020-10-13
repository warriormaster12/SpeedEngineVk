#pragma once 
#include "../Renderer/VkIncludes.h"
#include "../Renderer/VkModelLoader.h"
#include "../Renderer/VkSetup.h"
#include "../Renderer/Buffers/VkVertexbuffers.h"
#include "../Renderer/Buffers/VkIndexbuffers.h"
#include "../Renderer/Buffers/VkBufferCreation.h"
#include "../Math/Math3D.h"
#include "Textures.h"






namespace VkRenderer
{
    
    class Mesh 
    {
    public: 
        ModelLoader model_ref;
        VkvertexBuffer vertexBuffer_ref;
        VkindexBuffer indexBuffer_ref;  

        
        VkSetup *setup_ref;
        
        Transform3D mesh_transform;
        Texture2D DiffuseTexture;
        Texture2D NormalTexture;
        
        void InitMesh(VkSetup* setup, VkMemoryAllocator* memory_alloc, VkImageManager* image_m, VkCommandPool& commandPool);
        void update(uint32_t imageIndex);
        void DestroyMesh();
    };

}