#pragma once 

#include "VkIncludes.h"
#include "VkSetup.h"
#include "VkSwapChain.h"
#include "VkGraphicsPipeline.h"
#include "Buffers/VkFramebuffers.h"
#include "Buffers/VkCommandbuffers.h"

namespace VkRenderer
{
   
    class Renderer
    {
    public: 
        void InitVulkan(GLFWwindow *window);
        void DestroyVulkan();
    private: 
        VkSetup setup_ref;
        VkSwapChain swap_ref;
        VkGPipeline gpipeline_ref;
        VkframeBuffer Fbuffer_ref;
        VkcommandBuffer Cbuffer_ref;
    };
}







