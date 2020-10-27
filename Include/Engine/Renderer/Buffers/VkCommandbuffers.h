#pragma once 

#include "../VkIncludes.h"
#include "../VkSetup.h"
#include "../VkGraphicsPipeline.h"
#include "../VkRenderPass.h"
#include "../../Components/Scene.h"





namespace VkRenderer
{
    class VkcommandBuffer
    {
    public: 
        VkCommandPool commandPool;
        void createCommandPool(VkSurfaceKHR& surface);
        void createCommandBuffers(std::vector<VkFramebuffer> swapChainFramebuffers, VkExtent2D& swapChainExtent, std::vector<VkDescriptorSet>& descriptorSets);
        std::vector<VkCommandBuffer> commandBuffers;

        VkSetup *setup_ref;
        std::vector <VkGPipeline*> gpipeline_ref;
        VkRenderpass *renderpass_ref;
        PushConstants push_const;
        Scene *scene_ref;

    };
}