#pragma once 

#include "VkIncludes.h"
#include "VkSetup.h"

namespace VkRenderer
{
    class VkDraw
    {
    public: 
        void drawFrame(VkSetup& setup_ref, VkSwapchainKHR& swapChain, std::vector<VkCommandBuffer> commandBuffers);
        void createSyncObjects(VkSetup& setup_ref, std::vector<VkImage> swapChainImages);

        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        std::vector<VkFence> imagesInFlight;
        size_t currentFrame = 0;
        const int MAX_FRAMES_IN_FLIGHT = 2;
    };
}
