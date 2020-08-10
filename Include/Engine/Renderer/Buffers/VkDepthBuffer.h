#pragma once 

#include "../VkIncludes.h"
#include "../VkSetup.h"
#include "../../Components/Mesh.h"

namespace VkRenderer
{
    class VkDepthBuffer
    {
    public: 
        VkImage depthImage;
        VkDeviceMemory depthImageMemory;
        VkImageView depthImageView;

        VkSetup *setup_ref;
        Mesh *mesh_ref;

        void createDepthResources(VkExtent2D& swapChainExtent);
        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        VkFormat findDepthFormat();
        bool hasStencilComponent(VkFormat format);
    };
}