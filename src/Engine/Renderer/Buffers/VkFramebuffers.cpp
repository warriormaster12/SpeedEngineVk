#include "Engine/Renderer/Buffers/VkFramebuffers.h"

namespace VkRenderer
{
    void VkframeBuffer::createFramebuffers()
    {
        swapChainFramebuffers.resize(swap_ref->swapChainImageViews.size());

        for (size_t i = 0; i < swap_ref->swapChainImageViews.size(); i++) {
            VkImageView attachments[] = {
                swap_ref->swapChainImageViews[i]
            };

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = gpipeline_ref->renderPass;
            framebufferInfo.attachmentCount = 1;
            framebufferInfo.pAttachments = attachments;
            framebufferInfo.width = swap_ref->swapChainExtent.width;
            framebufferInfo.height = swap_ref->swapChainExtent.height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(setup_ref->device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create framebuffer!");
            }
        }
    }
}