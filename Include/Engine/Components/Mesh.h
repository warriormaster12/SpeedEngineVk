#pragma once 
#include "../Renderer/VkIncludes.h"
#include "../Renderer/VkTextureManager.h"
#include "../Renderer/VkModelLoader.h"
#include "../Renderer/VkSetup.h"
#include "../Renderer/VkSwapChain.h"
#include "../Renderer/Buffers/VkVertexbuffers.h"
#include "../Renderer/Buffers/VkIndexbuffers.h"
#include "../Renderer/Buffers/VkUnfiormbuffers.h"




namespace VkRenderer
{
    class Mesh 
    {
    public: 
        ModelLoader model_ref;
        VkTextureManager texture_m_ref;
        VkVbuffer Vbuffer_ref;
        VkindexBuffer Ibuffer_ref;  
        VkUbuffer Ubuffer_ref;
        VkSetup *setup_ref;
        VkSwapChain *swap_ref;
        
        Transform3D mesh_transform;
        
        Mesh();

        void InitMesh(VkCommandPool& commandPool);
        void update(uint32_t imageIndex);
        void DestroyMesh();
    };

}