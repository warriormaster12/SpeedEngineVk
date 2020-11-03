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

    void Vulkan::updateVulkan(UniformBufferObject& ubo, uint32_t byte_size)
    {
       vkWaitForFences(vulkanDevices.device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

        result = vkAcquireNextImageKHR(vulkanDevices.device, vulkanImages.vulkanSwapChain.swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);
        
        // if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        //     recreateSwapChain();
        //     return;
        // } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        //     throw std::runtime_error("failed to acquire swap chain image!");
        // }

        vulkanObjectBuffers.vulkanUniformBuffer.updateBuffer(imageIndex, ubo, byte_size);
        
        if (imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
            vkWaitForFences(vulkanDevices.device, 1, &imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
        }
        imagesInFlight[imageIndex] = inFlightFences[currentFrame];

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &vulkanCommandBuffer.commandBuffers[imageIndex];

        VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        vkResetFences(vulkanDevices.device, 1, &inFlightFences[currentFrame]);

        if (vkQueueSubmit(vulkanDevices.graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = {vulkanImages.vulkanSwapChain.swapChain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        result = vkQueuePresentKHR(vulkanDevices.presentQueue, &presentInfo);

        // if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || win->framebufferResized) {
        //     win->framebufferResized = false;
        //     recreateSwapChain();
        // } else if (result != VK_SUCCESS) {
        //     throw std::runtime_error("failed to present swap chain image!");
        // }

        currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
         
    }

    void Vulkan::destroyVulkan()
    {
        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroySemaphore(vulkanDevices.device, renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(vulkanDevices.device, imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(vulkanDevices.device, inFlightFences[i], nullptr);
        }
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