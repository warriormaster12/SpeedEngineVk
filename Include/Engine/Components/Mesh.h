#pragma once 

#include "../Renderer/VkTextureManager.h"
#include "../Renderer/VkModelLoader.h"
#include "../Renderer/Buffers/VkIndexbuffers.h"
#include "../Renderer/Buffers/VkVertexbuffers.h"



namespace VkRenderer
{
    class Mesh
    {
    public:
        void init_mesh(std::vector<VkImage>& swapChainImages, VkCommandPool& commandPool);

        ModelLoader model_ref;
        VkTextureManager texture_m_ref;
        VkVbuffer Vbuffer_ref;
        VkindexBuffer Ibuffer_ref;
        
    };
}