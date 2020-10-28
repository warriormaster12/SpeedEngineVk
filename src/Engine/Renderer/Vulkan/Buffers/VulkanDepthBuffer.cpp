#include "Engine/Renderer/Vulkan/Buffers/VulkanDepthBuffer.h"


namespace Renderer
{
    void VulkanDepthBuffer::initDepthBuffer(VulkanDevices& vulkanDevices, VulkanMemoryAllocator& vulkanMemoryAllocator, VulkanImageHandler& vulkanImageHandler)
    {
        p_vulkanDevices = &vulkanDevices;
        p_vulkanImageHandler = &vulkanImageHandler;
        p_vulkanMemoryAllocator = &vulkanMemoryAllocator;
    }
    void VulkanDepthBuffer::createDepthResources(VkExtent2D& swapChainExtent)
    {
        VkFormat depthFormat = findDepthFormat();
        VkImageCreateInfo depthInfo{};
        depthInfo.extent.width = swapChainExtent.width;
        depthInfo.extent.height = swapChainExtent.height;
        depthInfo.mipLevels = 1;
        depthInfo.format = depthFormat;
        depthInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        depthInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

        p_vulkanImageHandler->createImage(depthInfo, depthImage, depthImageAllocation);

        VkImageViewCreateInfo depthViewInfo{};
        depthViewInfo.image = depthImage;
        depthViewInfo.format = depthFormat;
        depthViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
        depthViewInfo.subresourceRange.levelCount = 1;

        depthImageView = p_vulkanImageHandler->createImageView(depthViewInfo);
    }
    VkFormat VulkanDepthBuffer::findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) {
        for (VkFormat format : candidates) {
            VkFormatProperties props;
            vkGetPhysicalDeviceFormatProperties(p_vulkanDevices->physicalDevice, format, &props);

            if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
                return format;
            } else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
                return format;
            }
        }

        throw std::runtime_error("failed to find supported format!");
    }

    VkFormat VulkanDepthBuffer::findDepthFormat() {
        return findSupportedFormat(
        {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
            VK_IMAGE_TILING_OPTIMAL,
            VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
        );
    }
    bool VulkanDepthBuffer::hasStencilComponent(VkFormat format) {
        return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
    }

    void VulkanDepthBuffer::destroyDepthBuffer()
    {
        vkDestroyImageView(p_vulkanDevices->device, depthImageView, nullptr);
        vmaDestroyImage(p_vulkanMemoryAllocator->allocator, depthImage, depthImageAllocation);
    }

}