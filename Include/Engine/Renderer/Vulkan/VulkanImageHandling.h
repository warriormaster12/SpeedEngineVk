#pragma once 

#include "VulkanIncludes.h"
#include "Buffers/VulkanImageBuffers.h"
#include "VulkanDevices.h"
#include "VulkanMemoryAllocator.h"


namespace Renderer
{
    class VulkanImageHandler
    {
    public: 
        void initImageHandler(VulkanDevices& vulkanDevices, VulkanMemoryAllocator& vulkanMemoryAllocator);
        VkImageView createImageView(VkImageViewCreateInfo& Info);
        void createImage(VkImageCreateInfo& Info, VkImage& image, VmaAllocation& imageAllocation);
        void transitionImageLayout(VkImageMemoryBarrier& barrierInfo, VkCommandPool& commandPool);
        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, VkCommandPool& commandPool);
        void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels, VkCommandPool& commandPool);

        
    
    private:
        VulkanDevices *p_vulkanDevices;
        VulkanImageBuffer vulkanImageBuffer;
        VulkanMemoryAllocator *p_vulkanMemoryAllocator;

       
        
    };
}