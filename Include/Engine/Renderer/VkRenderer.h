#pragma once 

#include "VkIncludes.h"
#include "VkSetup.h"
#include "VkSwapChain.h"
#include "VkGraphicsPipeline.h"
#include "Buffers/VkFramebuffers.h"
#include "Buffers/VkCommandbuffers.h"
#include "VkDraw.h"
#include "../Window/Window.h"

namespace VkRenderer
{
   
    class Renderer
    {
    public: 
        void InitVulkan(GLFWwindow *window);
        void UpdateVulkan();
        void DestroyVulkan();
        VkSetup setup_ref;
    private:  
        VkSwapChain swap_ref;
        VkGPipeline gpipeline_ref;
        VkframeBuffer Fbuffer_ref;
        VkcommandBuffer Cbuffer_ref;
        VkDraw draw_ref;
        AppWindow win_ref;
    };
}







