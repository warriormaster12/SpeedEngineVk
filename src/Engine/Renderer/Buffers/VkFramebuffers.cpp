#include "Engine/Renderer/Buffers/VkFramebuffers.h"

namespace VkRenderer
{
    void VkframeBuffer::createFramebuffers(VkMasterObject *vkobjects_ref, VkdepthBuffer *Dbuffer_ref,VkRenderpass *renderpass_ref)
    {
        swapChainFramebuffers.resize(vkobjects_ref->swap.swapChainImageViews.size());

        for (size_t i = 0; i < vkobjects_ref->swap.swapChainImageViews.size(); i++) {
            std::array<VkImageView, 2> attachments = {
                vkobjects_ref->swap.swapChainImageViews[i],
                Dbuffer_ref->depthImageView
            };

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = renderpass_ref->renderPass;
            framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
            framebufferInfo.pAttachments = attachments.data();
            framebufferInfo.width = vkobjects_ref->swap.swapChainExtent.width;
            framebufferInfo.height = vkobjects_ref->swap.swapChainExtent.height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(vkobjects_ref->setup.device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create framebuffer!");
            }
        }
    }
}