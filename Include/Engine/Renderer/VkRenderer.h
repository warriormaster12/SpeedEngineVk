#pragma once 

#include "VkIncludes.h"
#include "VkSetup.h"
#include "VkSwapChain.h"
#include "VkGraphicsPipeline.h"
#include "VkImageManager.h"
#include "VkRenderPass.h"
#include "Buffers/VkFramebuffers.h"
#include "Buffers/VkCommandbuffers.h"
#include "Buffers/VkBufferCreation.h"
#include "Buffers/VkDepthBuffer.h"
#include "Buffers/VkUniformbuffers.h"
#include "VkMemory.h"
#include "../Window/Window.h"
#include "../Components/Mesh.h"

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
        VkSetup setup_ref;
        AppWindow *win_ref;
        VkuniformBuffer uniformBuffer_ref;
        VkcommandBuffer Cbuffer_ref;
        
    private:  
        

        VkSwapChain swap_ref;
        VkGPipeline gpipeline_ref;
        VkGPipeline lightpipeline_ref;
        VkRenderpass renderpass_ref;
        VkframeBuffer Fbuffer_ref;
        
        std::vector <Mesh> meshes;
        
        VkImageManager image_m_ref;
        VkMemory memory_ref;
        VkbufferCreation buffer_ref;
        VkdepthBuffer Dbuffer_ref;

        

        
        
        
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        std::vector<VkFence> imagesInFlight;
        size_t currentFrame = 0;
        
        const int MAX_FRAMES_IN_FLIGHT = 2;


    
    };
}







