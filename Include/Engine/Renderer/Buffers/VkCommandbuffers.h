#pragma once 

#include "../VkIncludes.h"
#include "../VkSetup.h"
#include "../VkGraphicsPipeline.h"
#include "../../Components/Mesh.h"





namespace VkRenderer
{
    class VkcommandBuffer
    {
    public: 
        VkCommandPool commandPool;
        void createCommandPool(VkSurfaceKHR& surface);
        void createCommandBuffers(std::vector<VkFramebuffer> swapChainFramebuffers, VkExtent2D& swapChainExtent);
        std::vector<VkCommandBuffer> commandBuffers;

        VkSetup *setup_ref;
        VkGPipeline *gpipeline_ref;
        
        std::vector <Mesh> meshes;

    };
}