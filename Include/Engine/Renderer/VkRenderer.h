#pragma once 

#include "VkIncludes.h"
#include "VkSetup.h"
#include "VkSwapChain.h"
#include "VkGraphicsPipeline.h"
#include "VkImageManager.h"
#include "VkRenderPass.h"
#include "Buffers/VkUniformbuffers.h"
#include "Buffers/VkCommandbuffers.h"
#include "Buffers/VkFramebuffers.h"
#include "Buffers/VkBufferCreation.h"
#include "Buffers/VkDepthBuffer.h"
#include "VkMemoryAllocator.h"
#include "../Window/Window.h"
#include "../Components/Scene.h"

namespace VkRenderer
{
   
    class Renderer
    {
    public: 
        Renderer();

        void InitVulkan();
        void drawFrame();
        void createSyncObjects();
        void recreateSwapChain();
        void cleanupSwapChain();
        void DestroyVulkan();
        
        VkSetup setup;
        VkSwapChain swap;
        VkuniformBuffer uniformBuffer;
        VkcommandBuffer Cbuffer;
        Scene scene; 
        AppWindow *win; 
    private:  
        

        
        VkGPipeline gpipeline;
        VkGPipeline lightpipeline;
        VkRenderpass renderpass;
        VkframeBuffer Fbuffer;
        VkMemoryAllocator memory_alloc;
        
        
        VkImageManager image_m;
        VkbufferCreation buffer;
        VkdepthBuffer Dbuffer;

        

        
        
        
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        std::vector<VkFence> imagesInFlight;
        size_t currentFrame = 0;
        
        const int MAX_FRAMES_IN_FLIGHT = 2;


    
    };
}







