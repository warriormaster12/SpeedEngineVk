#pragma once 

#include "../VkIncludes.h"
#include "../VkSetup.h"
#include "../VkImageManager.h"

namespace VkRenderer
{
    class VkdepthBuffer
    {
    public: 
        VkImage depthImage;
        VmaAllocation depthImageAllocation;
        VkImageView depthImageView;

        VkSetup *setup_ref;
        VkImageManager *image_m_ref;

        void createDepthResources(VkExtent2D& swapChainExtent);
        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        VkFormat findDepthFormat();
        bool hasStencilComponent(VkFormat format);
    };
}