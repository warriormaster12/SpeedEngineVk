#include "Engine/Renderer/Vulkan/Buffers/VulkanFrameBuffer.h"

namespace Renderer
{
    void VulkanFrameBuffer::createFramebuffers(VulkanDevices& vulkanDevices, VulkanSwapChain& vulkanSwapChain, VulkanRenderPass& vulkanRenderPass)
    {
        swapChainFramebuffers.resize(vulkanSwapChain.swapChainImageViews.size());

        for (size_t i = 0; i < vulkanSwapChain.swapChainImageViews.size(); i++) {
            std::array<VkImageView, 2> attachments = {
                vulkanSwapChain.swapChainImageViews[i],
                vulkanRenderPass.depthImageView
            };

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = vulkanRenderPass.renderPass;
            framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
            framebufferInfo.pAttachments = attachments.data();
            framebufferInfo.width = vulkanSwapChain.swapChainExtent.width;
            framebufferInfo.height = vulkanSwapChain.swapChainExtent.height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(vulkanDevices.device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create framebuffer!");
            }
        }
    }

    void VulkanFrameBuffer::destroyFramebuffers(VulkanDevices& vulkanDevices)
    {
        for (auto framebuffer : swapChainFramebuffers) {
            vkDestroyFramebuffer(vulkanDevices.device, framebuffer, nullptr);
        }
    }
}