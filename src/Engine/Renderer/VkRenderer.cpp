#include "Engine/Renderer/VkRenderer.h"


namespace VkRenderer
{
    
    void Renderer::InitVulkan()
    {
        

        setup_ref.createInstance();
        setup_ref.setupDebugMessenger();
        swap_ref.createSurface(win_ref->window);
        swap_ref.pickPhysicalDevice();
        setup_ref.createLogicalDevice(swap_ref.surface);
        swap_ref.createSwapChain();
        swap_ref.createImageViews();
        gpipeline_ref.createRenderPass(swap_ref.swapChainImageFormat);
        Ubuffer_ref.createDescriptorSetLayout();
        gpipeline_ref.createGraphicsPipeline(swap_ref.swapChainExtent);
        Cbuffer_ref.createCommandPool(swap_ref.surface);
        Dbuffer_ref.createDepthResources(swap_ref.swapChainExtent);
        Fbuffer_ref.createFramebuffers();
    
        meshes.emplace_back();
        meshes.emplace_back();
        meshes.emplace_back();
        


        texture_m_ref.createTextureImage("EngineAssets/Textures/viking_room.png", Cbuffer_ref.commandPool);
        texture_m_ref.createTextureImageView();
        texture_m_ref.createTextureSampler();

        for (int i = 0; i < meshes.size(); i++) {
            //IndexBuffer
            meshes[i].Ibuffer_ref.setup_ref = &setup_ref;
            meshes[i].Ibuffer_ref.buffer_ref = &buffer_ref;

            //VertexBuffer
            meshes[i].Vbuffer_ref.setup_ref = &setup_ref;
            meshes[i].Vbuffer_ref.buffer_ref = &buffer_ref;
            
            //Mesh
            meshes[i].setup_ref = &setup_ref;

            meshes[i].InitMesh(Cbuffer_ref.commandPool);
            Ubuffer_ref.meshes.push_back(&meshes[i]);
            Cbuffer_ref.meshes.push_back(&meshes[i]);
        }
        

       
        Ubuffer_ref.createUniformBuffer(); 
        
        Ubuffer_ref.createDescriptorPool();
        Ubuffer_ref.createDescriptorSets(texture_m_ref.textureImageView,  texture_m_ref.textureSampler);
        
        

        Cbuffer_ref.createCommandBuffers(Fbuffer_ref.swapChainFramebuffers,swap_ref.swapChainExtent, Ubuffer_ref.descriptorSets);
        createSyncObjects();

        meshes[0].mesh_transform.translate=glm::vec3(0.0f,-1.0f,0.0f);
        meshes[1].mesh_transform.translate=glm::vec3(0.0f,1.0f,0.0f);
        meshes[2].mesh_transform.translate=glm::vec3(0.0f,0.0f,1.0f);
    }
    void Renderer::recreateSwapChain()
    {
        int width = 0, height = 0;
        glfwGetFramebufferSize(win_ref->window, &width, &height);
        while (width == 0 || height == 0) {
            glfwGetFramebufferSize(win_ref->window, &width, &height);
            glfwWaitEvents();
        }
        vkDeviceWaitIdle(setup_ref.device);

        cleanupSwapChain();

        swap_ref.createSwapChain();
        swap_ref.createImageViews();
        gpipeline_ref.createRenderPass(swap_ref.swapChainImageFormat);
        gpipeline_ref.createGraphicsPipeline(swap_ref.swapChainExtent);
        Dbuffer_ref.createDepthResources(swap_ref.swapChainExtent);
        Fbuffer_ref.createFramebuffers();
        
        Ubuffer_ref.createUniformBuffer();
        Ubuffer_ref.createDescriptorPool();
        Ubuffer_ref.createDescriptorSets(texture_m_ref.textureImageView, texture_m_ref.textureSampler);
        

        Cbuffer_ref.createCommandBuffers(Fbuffer_ref.swapChainFramebuffers,swap_ref.swapChainExtent, Ubuffer_ref.descriptorSets);
        

    }
    void Renderer::cleanupSwapChain()
    {
        vkDestroyImageView(setup_ref.device, Dbuffer_ref.depthImageView, nullptr);
        vkDestroyImage(setup_ref.device, Dbuffer_ref.depthImage, nullptr);
        vkFreeMemory(setup_ref.device, Dbuffer_ref.depthImageMemory, nullptr);
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
        for (size_t i = 0; i < meshes.size(); i++) {
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
        for (int i=meshes.size()-1; i >= 0; i--)
        {
            meshes[i].DestroyMesh();
        }

        
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


     void Renderer::drawFrame()
    {
        vkWaitForFences(setup_ref.device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(setup_ref.device, swap_ref.swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);
        
        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            recreateSwapChain();
            return;
        } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        for (int i=0; i < meshes.size(); i++)
        {
            Ubuffer_ref.updateUniformBuffer(i, swap_ref.swapChainExtent);
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

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || win_ref->framebufferResized) {
            win_ref->framebufferResized = false;
            recreateSwapChain();
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