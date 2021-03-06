#include "Engine/Renderer/Buffers/VkFramebuffers.h"

namespace VkRenderer
{
    void VkframeBuffer::createFramebuffers(VkSetup *setup_ref, VkSwapChain *swap_ref, VkdepthBuffer *Dbuffer_ref,VkRenderpass *renderpass_ref)
    {
        swapChainFramebuffers.resize(swap_ref->swapChainImageViews.size());

        for (size_t i = 0; i < swap_ref->swapChainImageViews.size(); i++) {
            std::array<VkImageView, 2> attachments = {
                swap_ref->swapChainImageViews[i],
                Dbuffer_ref->depthImageView
            };

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = renderpass_ref->renderPass;
            framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
            framebufferInfo.pAttachments = attachments.data();
            framebufferInfo.width = swap_ref->swapChainExtent.width;
            framebufferInfo.height = swap_ref->swapChainExtent.height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(setup_ref->device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create framebuffer!");
            }
        }
    }
}