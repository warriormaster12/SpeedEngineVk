#pragma once 

#include "VkIncludes.h"
#include "Buffers/VkBufferCreation.h"
#include "VkSetup.h"
#include "VkMemory.h"
#include "Buffers/VkCommandbuffers.h"

namespace VkRenderer
{
    class VkTextureManager
    {
    public: 
        void createTextureImage();
        void createTextureImageView();
        VkImageView createImageView(VkImage image, VkFormat format);
        void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

        VkSetup *setup_ref;
        VkBufferCreation *buffer_ref;
        VkMemory *memory_ref;
        VkcommandBuffer *Cbuffer_ref;

        VkImage textureImage;
        VkDeviceMemory textureImageMemory;
        VkImageView textureImageView;
    };
}