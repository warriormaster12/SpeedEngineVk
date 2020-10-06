#include "Engine/Renderer/VkRenderer.h"


namespace VkRenderer
{
    
    void Renderer::InitVulkan()
    {
        
        setup_ref.createInstance();
        setup_ref.setupDebugMessenger();
        swap_ref.createSurface();
        swap_ref.pickPhysicalDevice();
        setup_ref.createLogicalDevice(swap_ref.surface);
        swap_ref.createSwapChain();
        swap_ref.createImageViews();
        renderpass_ref.createRenderPass(setup_ref.device, swap_ref.swapChainImageFormat);
        uniformBuffer_ref.createDescriptorSetLayout();
        gpipeline_ref.shaders = {"EngineAssets/Shaders/Model_vert.vert", "EngineAssets/Shaders/Model_frag.frag",};
        gpipeline_ref.createGraphicsPipeline(swap_ref.swapChainExtent, renderpass_ref.renderPass,uniformBuffer_ref.descriptorSetLayout);
        lightpipeline_ref.shaders = {"EngineAssets/Shaders/light_cube_vert.vert", "EngineAssets/Shaders/light_cube_frag.frag",};;
        lightpipeline_ref.createGraphicsPipeline(swap_ref.swapChainExtent, renderpass_ref.renderPass,uniformBuffer_ref.descriptorSetLayout);
        Cbuffer_ref.createCommandPool(swap_ref.surface);
        Dbuffer_ref.createDepthResources(swap_ref.swapChainExtent);
        Fbuffer_ref.createFramebuffers();
    
        meshes.emplace_back();
        meshes.emplace_back();
        meshes.emplace_back();
        meshes.emplace_back();
        
        if(meshes.size() != 0)
        {
            meshes[2].DiffuseTexture.TEXTURE_PATH = "EngineAssets/Textures/chapel_diffuse.tga";
            meshes[2].NormalTexture.TEXTURE_PATH = "EngineAssets/Textures/chapel_normal.tga";
            meshes[2].model_ref.MODEL_PATH = "EngineAssets/Models/chapel_obj.obj";
            meshes[3].model_ref.MODEL_PATH = "EngineAssets/Models/cube.obj";

            

            for (int i = 0; i < meshes.size(); i++) {
                //Textures
                meshes[i].DiffuseTexture.image_m_ref = & image_m_ref;
                meshes[i].NormalTexture.image_m_ref = & image_m_ref;
                
                //IndexBuffer
                meshes[i].indexBuffer_ref.setup_ref = &setup_ref;
                meshes[i].indexBuffer_ref.buffer_ref = &buffer_ref;

                //VertexBuffer
                meshes[i].vertexBuffer_ref.setup_ref = &setup_ref;
                meshes[i].vertexBuffer_ref.buffer_ref = &buffer_ref;
                
                //Mesh
                meshes[i].setup_ref = &setup_ref;
                meshes[i].memory_ref = &memory_ref;
                meshes[i].buffer_ref = &buffer_ref;

                meshes[i].InitMesh(Cbuffer_ref.commandPool);
                uniformBuffer_ref.meshes.push_back(&meshes[i]);
                Cbuffer_ref.meshes.push_back(&meshes[i]);
            }
        
            
            
            uniformBuffer_ref.createUniformBuffer(); 
            
            uniformBuffer_ref.createDescriptorPool();
            uniformBuffer_ref.createDescriptorSets();

            

            meshes[0].mesh_transform.translate=glm::vec3(4.0f,0.0f,-2.0f);
            meshes[0].mesh_transform.rotation=glm::vec3(-90.0f,0.0f,-90.0f);
            
            meshes[1].mesh_transform.rotation=glm::vec3(-90.0f,0.0f,90.0f);
            meshes[1].mesh_transform.translate=glm::vec3(4.0f,0.0f,2.0f);

            meshes[2].mesh_transform.translate=glm::vec3(8.0f,0.0f,0.0f);
            meshes[2].mesh_transform.scale = glm::vec3(0.002f);
            meshes[2].mesh_transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
            meshes[3].mesh_transform.scale = glm::vec3(0.1);

            
            
        }     

        
        
        
        Cbuffer_ref.createCommandBuffers(Fbuffer_ref.swapChainFramebuffers,swap_ref.swapChainExtent, uniformBuffer_ref.descriptorSets);
        createSyncObjects();
       
        
        
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
        renderpass_ref.createRenderPass(setup_ref.device, swap_ref.swapChainImageFormat);
        gpipeline_ref.createGraphicsPipeline(swap_ref.swapChainExtent, renderpass_ref.renderPass,uniformBuffer_ref.descriptorSetLayout);
        lightpipeline_ref.createGraphicsPipeline(swap_ref.swapChainExtent, renderpass_ref.renderPass,uniformBuffer_ref.descriptorSetLayout);
        Dbuffer_ref.createDepthResources(swap_ref.swapChainExtent);
        Fbuffer_ref.createFramebuffers();
        
        if(meshes.size() != 0)
        {
            uniformBuffer_ref.createUniformBuffer();
            uniformBuffer_ref.createDescriptorPool();
            uniformBuffer_ref.createDescriptorSets();
        }
       
        Cbuffer_ref.createCommandBuffers(Fbuffer_ref.swapChainFramebuffers,swap_ref.swapChainExtent, uniformBuffer_ref.descriptorSets);
        

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
        vkDestroyPipeline(setup_ref.device, lightpipeline_ref.graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(setup_ref.device, lightpipeline_ref.pipelineLayout, nullptr);
        vkDestroyRenderPass(setup_ref.device, renderpass_ref.renderPass, nullptr);

        for (auto imageView : swap_ref.swapChainImageViews) {
            vkDestroyImageView(setup_ref.device, imageView, nullptr);
        }

        vkDestroySwapchainKHR(setup_ref.device, swap_ref.swapChain, nullptr);
        for (size_t i = 0; i < meshes.size(); i++) {
            vkDestroyBuffer(setup_ref.device, uniformBuffer_ref.uniformBuffers[i], nullptr);
            vkFreeMemory(setup_ref.device, uniformBuffer_ref.uniformBuffersMemory[i], nullptr);
            vkDestroyBuffer(setup_ref.device, uniformBuffer_ref.storageBuffers[i], nullptr);
            vkFreeMemory(setup_ref.device, uniformBuffer_ref.storageBuffersMemory[i], nullptr);
        }
        vkDestroyDescriptorPool(setup_ref.device, uniformBuffer_ref.descriptorPool, nullptr);
    }
    void Renderer::DestroyVulkan()
    {  
        cleanupSwapChain();
        
        

        vkDestroyDescriptorSetLayout(setup_ref.device, uniformBuffer_ref.descriptorSetLayout, nullptr);  
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
            uniformBuffer_ref.updateUniformBuffer(i, swap_ref.swapChainExtent);
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