#pragma once 

#include "../VkIncludes.h"
#include "../VkSetup.h"
#include "../VkGraphicsPipeline.h"
#include "../VkModelLoader.h"
#include "VkIndexbuffers.h"




namespace VkRenderer
{
    class VkcommandBuffer
    {
    public: 
        VkCommandPool commandPool;
        void createCommandPool(VkSurfaceKHR& surface);
        void createCommandBuffers(std::vector<VkFramebuffer> swapChainFramebuffers, VkExtent2D& swapChainExtent,std::vector<VkDescriptorSet> descriptorSets, VkBuffer& vertexBuffer, VkBuffer& indexBuffer);
        std::vector<VkCommandBuffer> commandBuffers;

        VkSetup *setup_ref;
        VkGPipeline *gpipeline_ref;
        VkindexBuffer *Ibuffer_ref;
        
        ModelLoader *model_ref;

    };
}