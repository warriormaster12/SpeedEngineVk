#include "Engine/Renderer/Buffers/VkDepthBuffer.h"


namespace VkRenderer
{
    void VkdepthBuffer::createDepthResources(VkExtent2D& swapChainExtent)
    {
        VkFormat depthFormat = findDepthFormat();
        VkImageCreateInfo depthInfo{};
        depthInfo.extent.width = swapChainExtent.width;
        depthInfo.extent.height = swapChainExtent.height;
        depthInfo.mipLevels = 1;
        depthInfo.format = depthFormat;
        depthInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        depthInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

        image_m_ref->createImage(depthInfo, depthImage, depthImageAllocation);

        VkImageViewCreateInfo depthViewInfo{};
        depthViewInfo.image = depthImage;
        depthViewInfo.format = depthFormat;
        depthViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
        depthViewInfo.subresourceRange.levelCount = 1;

        depthImageView = image_m_ref->createImageView(depthViewInfo);
    }
    VkFormat VkdepthBuffer::findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) {
        for (VkFormat format : candidates) {
            VkFormatProperties props;
            vkGetPhysicalDeviceFormatProperties(setup_ref->physicalDevice, format, &props);

            if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
                return format;
            } else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
                return format;
            }
        }

        throw std::runtime_error("failed to find supported format!");
    }

    VkFormat VkdepthBuffer::findDepthFormat() {
        return findSupportedFormat(
        {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
            VK_IMAGE_TILING_OPTIMAL,
            VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
        );
    }
    bool VkdepthBuffer::hasStencilComponent(VkFormat format) {
        return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
    }

}