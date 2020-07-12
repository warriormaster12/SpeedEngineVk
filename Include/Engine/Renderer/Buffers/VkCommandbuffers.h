#pragma once 

#include "../VkIncludes.h"
#include "../VkSetup.h"
#include "../VkGraphicsPipeline.h"


namespace VkRenderer
{
    class VkcommandBuffer
    {
    public: 
        VkCommandPool commandPool;
        void createCommandPool();
        void createCommandBuffers(std::vector<VkFramebuffer> swapChainFramebuffers, std::vector<VkDescriptorSet> descriptorSets, VkBuffer& vertexBuffer, VkBuffer& indexBuffer);
        std::vector<VkCommandBuffer> commandBuffers;

        VkSetup *setup_ref;
        VkSwapChain *swap_ref;
        VkGPipeline *Gpipeline_ref;
    };
}