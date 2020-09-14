#pragma once 

#include "VkIncludes.h"
#include "Buffers/VkBufferCreation.h"
#include "VkSetup.h"
#include "VkMemory.h"


namespace VkRenderer
{
    class VkTextureManager
    {
    public: 
        void createTextureImage(const std::string TEXTURE_PATH, VkCommandPool& commandPool);
        void createTextureImageView();
        void createTextureSampler();
        VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
        void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, VkCommandPool& commandPool, uint32_t mipLevels);
        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, VkCommandPool& commandPool);
        void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels, VkCommandPool& commandPool);

        VkSetup *setup_ref;
        VkbufferCreation *buffer_ref;
        VkMemory *memory_ref;

        uint32_t mipLevels;
        VkImage textureImage;
        VkDeviceMemory textureImageMemory;
        VkImageView textureImageView;
        VkSampler textureSampler;
    };
}