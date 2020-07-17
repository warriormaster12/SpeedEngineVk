#include "Engine/Renderer/VkRenderer.h"


namespace VkRenderer
{
    
    void Renderer::InitVulkan(GLFWwindow *window)
    {
        setup_ref.createInstance();
        setup_ref.setupDebugMessenger();
        swap_ref.createSurface(window);
        swap_ref.pickPhysicalDevice();
        setup_ref.createLogicalDevice(swap_ref.surface);
        swap_ref.createSwapChain();
        swap_ref.createImageViews();
        gpipeline_ref.createRenderPass(swap_ref.swapChainImageFormat);
        Ubuffer_ref.createDescriptorSetLayout();
        gpipeline_ref.createGraphicsPipeline(swap_ref.swapChainExtent);
        Fbuffer_ref.createFramebuffers();
        Cbuffer_ref.createCommandPool(swap_ref.surface);
        texture_m_ref.createTextureImage();
        texture_m_ref.createTextureImageView();
        texture_m_ref.createTextureSampler();
        Vbuffer_ref.createVertexBuffer(Cbuffer_ref.commandPool);
        Ibuffer_ref.createIndexBuffer(Cbuffer_ref.commandPool);
        Ubuffer_ref.createUniformBuffers(buffer_ref,swap_ref.swapChainImages);
        Ubuffer_ref.createDescriptorPool(swap_ref.swapChainImages);
        Ubuffer_ref.createDescriptorSets(swap_ref.swapChainImages, texture_m_ref.textureImageView, texture_m_ref.textureSampler);
        Cbuffer_ref.createCommandBuffers(Fbuffer_ref.swapChainFramebuffers,swap_ref.swapChainExtent, Ubuffer_ref.descriptorSets,Vbuffer_ref.vertexBuffer, Ibuffer_ref.indexBuffer);
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

        swap_ref.createSwapChain();
        swap_ref.createImageViews();
        gpipeline_ref.createRenderPass(swap_ref.swapChainImageFormat);
        gpipeline_ref.createGraphicsPipeline(swap_ref.swapChainExtent);
        Fbuffer_ref.createFramebuffers();
        Ubuffer_ref.createUniformBuffers(buffer_ref,swap_ref.swapChainImages);
        Ubuffer_ref.createDescriptorPool(swap_ref.swapChainImages);
        Ubuffer_ref.createDescriptorSets(swap_ref.swapChainImages, texture_m_ref.textureImageView, texture_m_ref.textureSampler);
        Cbuffer_ref.createCommandBuffers(Fbuffer_ref.swapChainFramebuffers,swap_ref.swapChainExtent, Ubuffer_ref.descriptorSets, Vbuffer_ref.vertexBuffer, Ibuffer_ref.indexBuffer);

    }
    void Renderer::cleanupSwapChain()
    {
        for (auto framebuffer : Fbuffer_ref.swapChainFramebuffers) {
            vkDestroyFramebuffer(setup_ref.device, framebuffer, nullptr);
        }

        vkFreeCommandBuffers(setup_ref.device, Cbuffer_ref.commandPool, static_cast<uint32_t>(Cbuffer_ref.commandBuffers.size()), Cbuffer_ref.commandBuffers.data());

        vkDestroyPipeline(setup_ref.device, gpipeline_ref.graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(setup_ref.device, gpipeline_ref.pipelineLayout, nullptr);
        vkDestroyRenderPass(setup_ref.device, gpipeline_ref.renderPass, nullptr);

        for (auto imageView : swap_ref.swapChainImageViews) {
            vkDestroyImageView(setup_ref.device, imageView, nullptr);
        }

        vkDestroySwapchainKHR(setup_ref.device, swap_ref.swapChain, nullptr);

        for (size_t i = 0; i < swap_ref.swapChainImages.size(); i++) {
            vkDestroyBuffer(setup_ref.device, Ubuffer_ref.uniformBuffers[i], nullptr);
            vkFreeMemory(setup_ref.device, Ubuffer_ref.uniformBuffersMemory[i], nullptr);
        }

        vkDestroyDescriptorPool(setup_ref.device, Ubuffer_ref.descriptorPool, nullptr);
    }
    void Renderer::DestroyVulkan()
    {  
        cleanupSwapChain();

        vkDestroySampler(setup_ref.device, texture_m_ref.textureSampler, nullptr);
        vkDestroyImageView(setup_ref.device, texture_m_ref.textureImageView, nullptr);

        vkDestroyImage(setup_ref.device, texture_m_ref.textureImage, nullptr);
        vkFreeMemory(setup_ref.device, texture_m_ref.textureImageMemory, nullptr);

        vkDestroyDescriptorSetLayout(setup_ref.device, Ubuffer_ref.descriptorSetLayout, nullptr);

        vkDestroyBuffer(setup_ref.device, Ibuffer_ref.indexBuffer, nullptr);
        vkFreeMemory(setup_ref.device, Ibuffer_ref.indexBufferMemory, nullptr);

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

        Ubuffer_ref.updateUniformBuffer(imageIndex, swap_ref.swapChainExtent);

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