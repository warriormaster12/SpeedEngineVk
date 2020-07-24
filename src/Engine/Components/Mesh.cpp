#include "Engine/Components/Mesh.h"

namespace VkRenderer
{
    void Mesh::init_mesh(std::vector<VkImage>& swapChainImages, VkCommandPool& commandPool)
    {
        texture_m_ref.createTextureImage(model_ref.TEXTURE_PATH, commandPool);
        texture_m_ref.createTextureImageView();
        texture_m_ref.createTextureSampler();
        model_ref.loadModel();
        Vbuffer_ref.createVertexBuffer(commandPool);
        Ibuffer_ref.createIndexBuffer(commandPool);
        
        
    }
}