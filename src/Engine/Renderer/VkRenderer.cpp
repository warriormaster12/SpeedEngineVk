#include "Engine/Renderer/VkRenderer.h"


namespace VkRenderer
{
    void Renderer::InitVulkan(GLFWwindow *window)
    {
        setup_ref.createInstance();
        setup_ref.setupDebugMessenger();
        swap_ref.createSurface(window, setup_ref.instance);
        setup_ref.pickPhysicalDevice(swap_ref.surface);
        setup_ref.createLogicalDevice(swap_ref.surface);
        swap_ref.createSwapChain(setup_ref, win_ref);
        swap_ref.createImageViews(setup_ref.device);
        gpipeline_ref.createRenderPass(setup_ref.device, swap_ref.swapChainImageFormat);
        gpipeline_ref.createGraphicsPipeline(setup_ref.device, swap_ref.swapChainExtent);
        Fbuffer_ref.createFramebuffers(setup_ref.device, swap_ref.swapChainImageViews, swap_ref.swapChainExtent, gpipeline_ref.renderPass);
        Cbuffer_ref.createCommandPool(setup_ref, swap_ref.surface);
        Vbuffer_ref.createVertexBuffer(setup_ref, memory_ref);
        Cbuffer_ref.createCommandBuffers(setup_ref.device, Fbuffer_ref.swapChainFramebuffers, swap_ref.swapChainExtent, gpipeline_ref, Vbuffer_ref);
        createSyncObjects();
    }
    void Renderer::recreateSwapChain(GLFWwindow *window)
    {
        int width = 0, height = 0;
        glfwGetFramebufferSize(window, &width, &height);
        while (width == 0 || height == 0) {
            glfwGetFramebufferSize(window, &width, &height);
            glfwWaitEvents();
        }
        vkDeviceWaitIdle(setup_ref.device);

        cleanupSwapChain();

        swap_ref.createSwapChain(setup_ref, win_ref);
        swap_ref.createImageViews(setup_ref.device);
        gpipeline_ref.createRenderPass(setup_ref.device, swap_ref.swapChainImageFormat);
        gpipeline_ref.createGraphicsPipeline(setup_ref.device, swap_ref.swapChainExtent);
        Fbuffer_ref.createFramebuffers(setup_ref.device, swap_ref.swapChainImageViews, swap_ref.swapChainExtent, gpipeline_ref.renderPass);
        Cbuffer_ref.createCommandBuffers(setup_ref.device, Fbuffer_ref.swapChainFramebuffers, swap_ref.swapChainExtent, gpipeline_ref, Vbuffer_ref);

    }
    void Renderer::cleanupSwapChain()
    {
        for (size_t i = 0; i <  Fbuffer_ref.swapChainFramebuffers.size(); i++) {
            vkDestroyFramebuffer(setup_ref.device, Fbuffer_ref.swapChainFramebuffers[i], nullptr);
        }

        vkFreeCommandBuffers(setup_ref.device, Cbuffer_ref.commandPool, static_cast<uint32_t>(Cbuffer_ref.commandBuffers.size()), Cbuffer_ref.commandBuffers.data());

        vkDestroyPipeline(setup_ref.device, gpipeline_ref.graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(setup_ref.device, gpipeline_ref.pipelineLayout, nullptr);
        vkDestroyRenderPass(setup_ref.device, gpipeline_ref.renderPass, nullptr);

        for (size_t i = 0; i < swap_ref.swapChainImageViews.size(); i++) {
            vkDestroyImageView(setup_ref.device, swap_ref.swapChainImageViews[i], nullptr);
        }

        vkDestroySwapchainKHR(setup_ref.device, swap_ref.swapChain, nullptr);
    }
    void Renderer::DestroyVulkan()
    {  
        cleanupSwapChain();

        vkDestroyBuffer(setup_ref.device, Vbuffer_ref.vertexBuffer, nullptr);
        vkFreeMemory(setup_ref.device, Vbuffer_ref.vertexBufferMemory, nullptr);

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroySemaphore(setup_ref.device, renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(setup_ref.device, imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(setup_ref.device, inFlightFences[i], nullptr);
        }
        vkDestroyCommandPool(setup_ref.device, Cbuffer_ref.commandPool, nullptr);
        
        vkDestroyDevice(setup_ref.device, nullptr);
         if (enableValidationLayers) {
            setup_ref.DestroyDebugUtilsMessengerEXT(setup_ref.debugMessenger, nullptr);
        }
        vkDestroySurfaceKHR(setup_ref.instance, swap_ref.surface, nullptr);
        vkDestroyInstance(setup_ref.instance, nullptr);
    }


     void Renderer::drawFrame(GLFWwindow *window)
    {
        vkWaitForFences(setup_ref.device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(setup_ref.device, swap_ref.swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            recreateSwapChain(window);
            return;
        } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        if (imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
            vkWaitForFences(setup_ref.device, 1, &imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
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
        submitInfo.pCommandBuffers = &Cbuffer_ref.commandBuffers[imageIndex];

        VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        vkResetFences(setup_ref.device, 1, &inFlightFences[currentFrame]);

        if (vkQueueSubmit(setup_ref.graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = {swap_ref.swapChain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        result = vkQueuePresentKHR(setup_ref.presentQueue, &presentInfo);

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
            framebufferResized = false;
            recreateSwapChain(window);
        } else if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image!");
        }

        currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    }
    void Renderer::createSyncObjects()
    {
        imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
        imagesInFlight.resize(swap_ref.swapChainImages.size(), VK_NULL_HANDLE);

        VkSemaphoreCreateInfo semaphoreInfo{};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            if (vkCreateSemaphore(setup_ref.device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
                vkCreateSemaphore(setup_ref.device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
                vkCreateFence(setup_ref.device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create synchronization objects for a frame!");
            }
        }
    }
}