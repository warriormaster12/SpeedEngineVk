#include "Engine/Renderer/Vulkan/VulkanRenderer.h"

namespace Renderer
{
    void Vulkan::initVulkan(AppWindow& win)
    {
        vulkanDevices.initializeDevices();
        vulkanImages.vulkanSwapChain.initializeSwapChain(vulkanDevices, win);
        vulkanDevices.createLogicalDevice(vulkanImages.vulkanSwapChain.surface);
        vulkanMemoryAllocator.createAllocator(vulkanDevices);
        vulkanImages.initImages(vulkanDevices, vulkanMemoryAllocator, win);        
    }

    void Vulkan::updateVulkan(double deltaTime)
    {
        
    }

    void Vulkan::destroyVulkan()
    {
        vulkanGraphicsPipeline.destroyPipeline(vulkanDevices);
        vulkanImages.destroyImages(vulkanDevices);
        vulkanMemoryAllocator.destroyAllocator();
        vulkanDevices.destroyDevices();
    }

    void Vulkan::createSyncObjects()
    {
        imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
        imagesInFlight.resize(vulkanImages.vulkanSwapChain.swapChainImages.size(), VK_NULL_HANDLE);

        VkSemaphoreCreateInfo semaphoreInfo{};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            if (vkCreateSemaphore(vulkanDevices.device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
                vkCreateSemaphore(vulkanDevices.device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
                vkCreateFence(vulkanDevices.device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create synchronization objects for a frame!");
            }
        }
    }
}