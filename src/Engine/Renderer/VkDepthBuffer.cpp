#include "Engine/Renderer/VkDepthBuffer.h"
#include "Engine/Renderer/VkRenderer.h"

namespace VkRenderer
{
    extern VkDepthBuffer DBuffer_ref;
    void Renderer::createDepthResources()
    {
        VkFormat depthFormat = DBuffer_ref.findDepthFormat(physicalDevice);

        createImage(swapChainExtent.width, swapChainExtent.height, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, DBuffer_ref.depthImage, DBuffer_ref.depthImageMemory);
        DBuffer_ref.depthImageView = createImageView(DBuffer_ref.depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
    }
    VkFormat VkDepthBuffer::findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features, VkPhysicalDevice physicalDevice)
    {
         for (VkFormat format : candidates) {
            VkFormatProperties props;
            vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

            if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
                return format;
            } else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
                return format;
            }
        }

        throw std::runtime_error("failed to find supported format!");

    }
    VkFormat VkDepthBuffer::findDepthFormat(VkPhysicalDevice physicalDevice) {
        return findSupportedFormat(
        {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
            VK_IMAGE_TILING_OPTIMAL,
            VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT,
            physicalDevice
        );
    }
    bool VkDepthBuffer::hasStencilComponent(VkFormat format) {
        return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
    }
    
}