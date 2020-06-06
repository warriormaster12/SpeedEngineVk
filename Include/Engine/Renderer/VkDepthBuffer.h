#pragma once 

#include "VkIncludes.h"

namespace VkRenderer
{
    class VkDepthBuffer
    {
    public:
        
        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features, VkPhysicalDevice physicalDevice);
        VkFormat findDepthFormat(VkPhysicalDevice physicalDevice);
        VkImage depthImage;
        VkDeviceMemory depthImageMemory;
        VkImageView depthImageView;
        bool hasStencilComponent(VkFormat format);
    };
}