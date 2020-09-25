#pragma once 

#include "VkIncludes.h"
#include "Buffers/VkDepthBuffer.h"



namespace VkRenderer
{
    class VkRenderpass
    {
    public: 
        void createRenderPass(VkDevice& device, VkFormat& swapChainImageFormat);

        VkdepthBuffer *Dbuffer_ref;
        VkRenderPass renderPass;
    };
}