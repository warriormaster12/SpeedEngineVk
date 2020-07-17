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
        void createTextureImage(VkCommandPool& commandPool);
        void createTextureImageView();
        void createTextureSampler();
        VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
        void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, VkCommandPool& commandPool);
        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, VkCommandPool& commandPool);

        VkSetup *setup_ref;
        VkBufferCreation *buffer_ref;
        VkMemory *memory_ref;

        VkImage textureImage;
        VkDeviceMemory textureImageMemory;
        VkImageView textureImageView;
        VkSampler textureSampler;
    };
}