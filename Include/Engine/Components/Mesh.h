#pragma once 
#include "../Renderer/VkIncludes.h"
#include "../Renderer/VkModelLoader.h"
#include "../Renderer/VkSetup.h"
#include "../Renderer/Buffers/VkVertexbuffers.h"
#include "../Renderer/Buffers/VkIndexbuffers.h"
#include "../Renderer/Buffers/VkBufferCreation.h"
#include "../Renderer/VkMemory.h"
#include "../Math/Math3D.h"
#include "../Renderer/VkTextureManager.h"






namespace VkRenderer
{
    
    class Mesh 
    {
    public: 
        ModelLoader model_ref;
        VkVbuffer Vbuffer_ref;
        VkindexBuffer Ibuffer_ref;  

        
        VkSetup *setup_ref;
        VkMemory *memory_ref;
        VkBufferCreation *buffer_ref;
        
        Transform3D mesh_transform;
        VkTextureManager texture;
        std::string TEXTURE_PATH = "EngineAssets/Textures/viking_room.png";
        
        
        void BindTexture(VkCommandPool& commandPool);
        void DestroyTexture();
        void InitMesh(VkCommandPool& commandPool);
        void update(uint32_t imageIndex);
        void DestroyMesh();
    };

}