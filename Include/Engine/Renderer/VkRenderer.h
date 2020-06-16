#pragma once 

#include "VkIncludes.h"
#include "VkSetup.h"
#include "VkSwapChain.h"
#include "VkGraphicsPipeline.h"
#include "Buffers/VkFramebuffers.h"
#include "Buffers/VkCommandbuffers.h"
#include "../Window/Window.h"

namespace VkRenderer
{
   
    class Renderer
    {
    public: 
        void InitVulkan(GLFWwindow *window);
        void drawFrame(GLFWwindow *window);
        void createSyncObjects();
        void recreateSwapChain(GLFWwindow *window);
        void cleanupSwapChain();
        void DestroyVulkan();
        VkSetup setup_ref;
        bool framebufferResized = false;
    private:  
        VkSwapChain swap_ref;
        VkGPipeline gpipeline_ref;
        VkframeBuffer Fbuffer_ref;
        VkcommandBuffer Cbuffer_ref;
        AppWindow win_ref;
        
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        std::vector<VkFence> imagesInFlight;
        size_t currentFrame = 0;
        
        const int MAX_FRAMES_IN_FLIGHT = 2;


    
    };
}







