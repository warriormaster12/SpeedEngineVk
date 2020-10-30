#pragma once 

#include "VulkanDevices.h"
#include "VulkanImages.h"
#include "VulkanMemoryAllocator.h"
#include "VulkanGraphicsPipeline.h"
#include "ObjectBuffers/VulkanObjectBuffers.h"
#include "VulkanModelLoader.h"
#include "Buffers/VulkanCommandBuffers.h"

namespace Renderer
{
    class Vulkan
    {
    public: 
        void initVulkan(AppWindow& win);
        void updateVulkan(double deltaTime);
        void destroyVulkan();
    
        VulkanDevices vulkanDevices;
        VulkanImages vulkanImages;
        VulkanObjectBuffers vulkanObjectBuffers;
        VulkanGraphicsPipeline vulkanGraphicsPipeline;
        VulkanMemoryAllocator vulkanMemoryAllocator;
        VulkanCommandBuffer vulkanCommandBuffer;
        VulkanModelLoader vulkanModelLoader;
    private:
        void createSyncObjects();
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        std::vector<VkFence> imagesInFlight;
        size_t currentFrame = 0;
        
        const int MAX_FRAMES_IN_FLIGHT = 2;
    };
    
}