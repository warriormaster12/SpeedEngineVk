#pragma once 

#include "VkIncludes.h"
#include "VkSetup.h"
#include "VkSwapChain.h"

namespace VkRenderer
{
   
    class Renderer
    {
    public: 
        void InitVulkan(GLFWwindow *window);
        void DestroyVulkan();
        VkSetup setup_ref;
        VkSwapChain swap_ref;
        
        
    };
}







