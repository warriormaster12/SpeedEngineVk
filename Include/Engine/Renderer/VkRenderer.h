#pragma once 

#include "VkIncludes.h"
#include "VkSetup.h"
#include "VkSwapChain.h"
#include "VkGraphicsPipeline.h"

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
        
    };
}







