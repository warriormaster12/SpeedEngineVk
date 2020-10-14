#include "Engine/Renderer/VkRenderer.h"


namespace VkRenderer
{
    Renderer::Renderer()
    {

        //GraphicsPipeline
        gpipeline_ref.setup_ref = &setup;
        lightpipeline_ref.setup_ref = &setup;

        //RenderPass
        renderpass_ref.Dbuffer_ref = &Dbuffer_ref;

        //UniformBuffer
        uniformBuffer.camera_object.win_ref = &win_ref;
        
        //BufferCreation
        buffer_ref.setup_ref = &setup;
        
        

        //CommandBuffer
        Cbuffer.setup_ref = &setup;
        Cbuffer.gpipeline_ref = &gpipeline_ref;
        Cbuffer.lightpipeline_ref = &lightpipeline_ref;
        Cbuffer.renderpass_ref = &renderpass_ref;
        
        //DepthBuffer
        Dbuffer_ref.setup_ref = &setup;
        Dbuffer_ref.image_m_ref = &image_m_ref;

        //imageManager
        image_m_ref.setup_ref = &setup;
        image_m_ref.buffer_ref = &buffer_ref;
        image_m_ref.memory_alloc_ref = &memory_alloc;
    }
    
    void Renderer::InitVulkan()
    {
        
        setup.Initialize();
        swap.Initialize(&setup, win_ref, &image_m_ref);
        setup.createLogicalDevice(swap.surface);
        memory_alloc.createAllocator(setup);
        swap.createSwapChain();
        swap.createImageViews();
        renderpass_ref.createRenderPass(setup.device, swap.swapChainImageFormat);
        uniformBuffer.Initialize(&setup, &memory_alloc);
        gpipeline_ref.shaders = {"EngineAssets/Shaders/Model_vert.vert", "EngineAssets/Shaders/Model_frag.frag",};
        gpipeline_ref.createGraphicsPipeline(swap.swapChainExtent, renderpass_ref.renderPass,uniformBuffer.descriptorSetLayout);
        lightpipeline_ref.shaders = {"EngineAssets/Shaders/light_cube_vert.vert", "EngineAssets/Shaders/light_cube_frag.frag",};
        lightpipeline_ref.vertex_attributes = 1; 
        lightpipeline_ref.createGraphicsPipeline(swap.swapChainExtent, renderpass_ref.renderPass,uniformBuffer.descriptorSetLayout);
        Cbuffer.createCommandPool(swap.surface);
        Dbuffer_ref.createDepthResources(swap.swapChainExtent);
        Fbuffer_ref.createFramebuffers(&setup, &swap, &Dbuffer_ref, &renderpass_ref);
    
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
            meshes[3].current_mesh_type = mesh_types::preview;

            

            for (int i = 0; i < meshes.size(); i++) {
                meshes[i].InitMesh(&setup, &memory_alloc, &image_m_ref,Cbuffer.commandPool);
                uniformBuffer.meshes.push_back(&meshes[i]);
                Cbuffer.meshes.push_back(&meshes[i]);
            }
        
            
            
            uniformBuffer.createUniformBuffer(); 
            
            uniformBuffer.createDescriptorPool();
            uniformBuffer.createDescriptorSets();

            

            meshes[0].mesh_transform.translate=glm::vec3(4.0f,0.0f,-2.0f);
            meshes[0].mesh_transform.rotation=glm::vec3(-90.0f,0.0f,-90.0f);
            
            meshes[1].mesh_transform.rotation=glm::vec3(-90.0f,0.0f,90.0f);
            meshes[1].mesh_transform.translate=glm::vec3(4.0f,0.0f,2.0f);

            meshes[2].mesh_transform.translate=glm::vec3(8.0f,0.0f,0.0f);
            meshes[2].mesh_transform.scale = glm::vec3(0.002f);
            meshes[2].mesh_transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
            meshes[3].mesh_transform.scale = glm::vec3(0.1);
            
        }     

        
        
        
        Cbuffer.createCommandBuffers(Fbuffer_ref.swapChainFramebuffers,swap.swapChainExtent, uniformBuffer.descriptorSets);
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
        vkDeviceWaitIdle(setup.device);

        cleanupSwapChain();

        swap.createSwapChain();
        swap.createImageViews();
        renderpass_ref.createRenderPass(setup.device, swap.swapChainImageFormat);
        gpipeline_ref.createGraphicsPipeline(swap.swapChainExtent, renderpass_ref.renderPass,uniformBuffer.descriptorSetLayout);
        lightpipeline_ref.createGraphicsPipeline(swap.swapChainExtent, renderpass_ref.renderPass,uniformBuffer.descriptorSetLayout);
        Dbuffer_ref.createDepthResources(swap.swapChainExtent);
        Fbuffer_ref.createFramebuffers(&setup, &swap, &Dbuffer_ref, &renderpass_ref);
        
        if(meshes.size() != 0)
        {
            uniformBuffer.createUniformBuffer();
            uniformBuffer.createDescriptorPool();
            uniformBuffer.createDescriptorSets();
        }
       
        Cbuffer.createCommandBuffers(Fbuffer_ref.swapChainFramebuffers,swap.swapChainExtent, uniformBuffer.descriptorSets);
        

    }
    void Renderer::cleanupSwapChain()
    {
        
        vkDestroyImageView(setup.device, Dbuffer_ref.depthImageView, nullptr);
        vmaDestroyImage(memory_alloc.allocator, Dbuffer_ref.depthImage, Dbuffer_ref.depthImageAllocation);
        for (auto framebuffer : Fbuffer_ref.swapChainFramebuffers) {
            vkDestroyFramebuffer(setup.device, framebuffer, nullptr);
        }

        vkFreeCommandBuffers(setup.device, Cbuffer.commandPool, static_cast<uint32_t>(Cbuffer.commandBuffers.size()), Cbuffer.commandBuffers.data());

        vkDestroyPipeline(setup.device, gpipeline_ref.graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(setup.device, gpipeline_ref.pipelineLayout, nullptr);
        vkDestroyPipeline(setup.device, lightpipeline_ref.graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(setup.device, lightpipeline_ref.pipelineLayout, nullptr);
        vkDestroyRenderPass(setup.device, renderpass_ref.renderPass, nullptr);

        for (auto imageView : swap.swapChainImageViews) {
            vkDestroyImageView(setup.device, imageView, nullptr);
        }

        vkDestroySwapchainKHR(setup.device, swap.swapChain, nullptr);
        uniformBuffer.DestroyUniformBuffer();
        vkDestroyDescriptorPool(setup.device, uniformBuffer.descriptorPool, nullptr);
    }
    void Renderer::DestroyVulkan()
    {  
        cleanupSwapChain();
        
        
        

        vkDestroyDescriptorSetLayout(setup.device, uniformBuffer.descriptorSetLayout, nullptr);  
        for (int i=meshes.size()-1; i >= 0; i--)
        {
            meshes[i].DestroyMesh();
        }
        

        
        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroySemaphore(setup.device, renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(setup.device, imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(setup.device, inFlightFences[i], nullptr);
        }
        vkDestroyCommandPool(setup.device, Cbuffer.commandPool, nullptr);
        
        vmaDestroyAllocator(memory_alloc.allocator);
        vkDestroyDevice(setup.device, nullptr);
        if (enableValidationLayers) {
            setup.DestroyDebugUtilsMessengerEXT(setup.debugMessenger, nullptr);
        }
        vkDestroySurfaceKHR(setup.instance, swap.surface, nullptr);
        vkDestroyInstance(setup.instance, nullptr);
        
        
    }


     void Renderer::drawFrame()
    {
        vkWaitForFences(setup.device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(setup.device, swap.swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);
        
        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            recreateSwapChain();
            return;
        } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }
        
        for (int i=0; i < meshes.size(); i++)
        {
            uniformBuffer.updateUniformBuffer(i, swap.swapChainExtent);
        }

        

        if (imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
            vkWaitForFences(setup.device, 1, &imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
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
        submitInfo.pCommandBuffers = &Cbuffer.commandBuffers[imageIndex];

        VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        vkResetFences(setup.device, 1, &inFlightFences[currentFrame]);

        if (vkQueueSubmit(setup.graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = {swap.swapChain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        result = vkQueuePresentKHR(setup.presentQueue, &presentInfo);

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
        imagesInFlight.resize(swap.swapChainImages.size(), VK_NULL_HANDLE);

        VkSemaphoreCreateInfo semaphoreInfo{};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            if (vkCreateSemaphore(setup.device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
                vkCreateSemaphore(setup.device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
                vkCreateFence(setup.device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create synchronization objects for a frame!");
            }
        }
    }
}