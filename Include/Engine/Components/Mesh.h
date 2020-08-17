#pragma once 
#include "../Renderer/VkIncludes.h"
#include "../Renderer/VkModelLoader.h"
#include "../Renderer/VkSetup.h"
#include "../Renderer/Buffers/VkVertexbuffers.h"
#include "../Renderer/Buffers/VkIndexbuffers.h"
#include "../Math/Math3D.h"






namespace VkRenderer
{
    
    class Mesh 
    {
    public: 
        ModelLoader model_ref;
        VkVbuffer Vbuffer_ref;
        VkindexBuffer Ibuffer_ref;  

        
        VkSetup *setup_ref;
        
        Transform3D mesh_transform;
        std::string TEXTURE_PATH = "EngineAssets/Textures/viking_room.png";
        
        

        void InitMesh(VkCommandPool& commandPool);
        void update(uint32_t imageIndex);
        void DestroyMesh();
    };

}