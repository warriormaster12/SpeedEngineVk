#pragma once 

#include "../VkIncludes.h"
#include "../VkSetup.h"
#include "../VkTextureManager.h"

namespace VkRenderer
{
    class VkDepthBuffer
    {
    public: 
        VkImage depthImage;
        VkDeviceMemory depthImageMemory;
        VkImageView depthImageView;

        VkSetup *setup_ref;
        VkTextureManager *texture_m_ref;

        void createDepthResources(VkExtent2D& swapChainExtent);
        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        VkFormat findDepthFormat();
        bool hasStencilComponent(VkFormat format);
    };
}