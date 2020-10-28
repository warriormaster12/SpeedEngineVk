#pragma once 

#include "../VulkanIncludes.h"
#include "../VulkanDevices.h"
#include "../VulkanImageHandling.h"

namespace Renderer
{
    class VulkanDepthBuffer
    {
    public: 
        VkImage depthImage;
        VmaAllocation depthImageAllocation;
        VkImageView depthImageView;

        VulkanDevices *p_vulkanDevices;
        VulkanImageHandler *p_vulkanImageHandler;
        VulkanMemoryAllocator *p_vulkanMemoryAllocator;
        
        void initDepthBuffer(VulkanDevices& vulkanDevices, VulkanMemoryAllocator& vulkanMemoryAllocator, VulkanImageHandler& vulkanImageHandler);
        void createDepthResources(VkExtent2D& swapChainExtent);
        void destroyDepthBuffer();
        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        VkFormat findDepthFormat();
        bool hasStencilComponent(VkFormat format);
    };
}