#pragma once 

#include "../Renderer/VkIncludes.h"
#include "../Renderer/VkImageManager.h"
#include "../Renderer/VkMemoryAllocator.h"



struct Texture2D
{
    void BindTexture(VkCommandPool& commandPool);
    void createTextureImage(VkCommandPool& commandPool);
    void createTextureImageView();
    void createTextureSampler();
    void DestroyTexture();
    std::string TEXTURE_PATH = "EngineAssets/Textures/viking_room.png";

    VkRenderer::VkImageManager *image_m_ref;
    VkMemoryAllocator *memory_alloc_ref;

    uint32_t mipLevels;
    VkImage textureImage;
    VkDeviceMemory textureImageMemory;

    VkImageView textureImageView;
    VkSampler textureSampler;
};