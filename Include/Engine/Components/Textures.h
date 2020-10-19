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
    VmaAllocation textureImageAllocation;

    VkImageView textureImageView;
    VkSampler textureSampler;
};

struct CubeMapTexture
{
    void BindTexture(VkCommandPool& commandPool);
    void createCubeMapTextureImage(VkCommandPool& commandPool);
    void createCubeMapTextureImageView();
    void createCubeMapTextureSampler();
    void DestroyTexture();
    
    std::vector <std::string> TEXTURE_PATHS = {
        "EngineAssets/Textures/skybox/back.jpg", 
        "EngineAssets/Textures/skybox/bottom.jpg", 
        "EngineAssets/Textures/skybox/front.jpg",
        "EngineAssets/Textures/skybox/left.jpg",
        "EngineAssets/Textures/skybox/right.jpg",
        "EngineAssets/Textures/skybox/top.jpg"
    };

    VkRenderer::VkImageManager *image_m_ref;
    VkMemoryAllocator *memory_alloc_ref;

    uint32_t mipLevels;
    VkImage textureImage;
    VmaAllocation textureImageAllocation;

    VkImageView textureImageView;
    VkSampler textureSampler;
};