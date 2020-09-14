#pragma once 

#include "../Renderer/VkIncludes.h"
#include "../Renderer/VkImageManager.h"



struct Texture2D
{
    void BindTexture(const std::string TEXTURE_PATH,VkCommandPool& commandPool);
    void createTextureImage(const std::string TEXTURE_PATH, VkCommandPool& commandPool);
    void createTextureImageView();
    void createTextureSampler();
    void DestroyTexture();
    VkRenderer::VkImageManager *image_m_ref;

    uint32_t mipLevels;
    VkImage textureImage;
    VkDeviceMemory textureImageMemory;

    VkImageView textureImageView;
    VkSampler textureSampler;
};