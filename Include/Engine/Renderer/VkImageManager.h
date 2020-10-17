#pragma once 

#include "VkIncludes.h"
#include "Buffers/VkBufferCreation.h"
#include "VkSetup.h"
#include "VkMemoryAllocator.h"


namespace VkRenderer
{
    class VkImageManager
    {
    public: 
        
        VkImageView createImageView(VkImageViewCreateInfo Info);
        void createImage(VkImageCreateInfo& Info, VkImage& image, VmaAllocation& imageAllocation);
        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, VkCommandPool& commandPool, uint32_t mipLevels);
        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, VkCommandPool& commandPool);
        void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels, VkCommandPool& commandPool);

        VkSetup *setup_ref;
        VkbufferCreation *buffer_ref;
        VkMemoryAllocator *memory_alloc_ref;

       
        
    };
}