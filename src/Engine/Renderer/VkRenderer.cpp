#include "Engine/Renderer/VkRenderer.h"


namespace VkRenderer
{
    Renderer::Renderer()
    {

        //GraphicsPipeline
        gpipeline.setup_ref = &setup;
        lightpipeline.setup_ref = &setup;

        //RenderPass
        renderpass.Dbuffer_ref = &Dbuffer;

        
        //BufferCreation
        buffer.setup_ref = &setup;
        
        

        //CommandBuffer
        Cbuffer.setup_ref = &setup;
        Cbuffer.gpipeline_ref = &gpipeline;
        Cbuffer.lightpipeline_ref = &lightpipeline;
        Cbuffer.renderpass_ref = &renderpass;
        
        //DepthBuffer
        Dbuffer.setup_ref = &setup;
        Dbuffer.image_m_ref = &image_m;

        //imageManager
        image_m.setup_ref = &setup;
        image_m.buffer_ref = &buffer;
        image_m.memory_alloc_ref = &memory_alloc;
    }
    
    void Renderer::InitVulkan()
    {
        
        setup.Initialize();
        swap.Initialize(&setup, win, &image_m);
        setup.createLogicalDevice(swap.surface);
        memory_alloc.createAllocator(setup);
        swap.createSwapChain();
        swap.createImageViews();
        renderpass.createRenderPass(setup.device, swap.swapChainImageFormat);
        uniformBuffer.Initialize(&setup, &memory_alloc);
        gpipeline.shaders = {"EngineAssets/Shaders/Model_vert.vert", "EngineAssets/Shaders/Model_frag.frag",};
        gpipeline.createGraphicsPipeline(swap.swapChainExtent, renderpass.renderPass,uniformBuffer.descriptorSetLayout);
        lightpipeline.shaders = {"EngineAssets/Shaders/light_cube_vert.vert", "EngineAssets/Shaders/light_cube_frag.frag",};
        lightpipeline.vertex_attributes = 1; 
        lightpipeline.createGraphicsPipeline(swap.swapChainExtent, renderpass.renderPass,uniformBuffer.descriptorSetLayout);
        Cbuffer.createCommandPool(swap.surface);
        Dbuffer.createDepthResources(swap.swapChainExtent);
        Fbuffer.createFramebuffers(&setup, &swap, &Dbuffer, &renderpass);
    
        meshes.emplace_back();
        meshes.emplace_back();
        meshes.emplace_back();
        meshes.emplace_back();
        
        if(meshes.size() != 0)
        {
            meshes[2].DiffuseTexture.TEXTURE_PATH = "EngineAssets/Textures/chapel_diffuse.tga";
            meshes[2].NormalTexture.TEXTURE_PATH = "EngineAssets/Textures/chapel_normal.tga";
            meshes[2].model.MODEL_PATH = "EngineAssets/Models/chapel_obj.obj";
            meshes[3].model.MODEL_PATH = "EngineAssets/Models/cube.obj";
            meshes[3].current_mesh_type = mesh_types::preview;

            

            for (int i = 0; i < meshes.size(); i++) {
                meshes[i].InitMesh(&setup, &memory_alloc, &image_m,Cbuffer.commandPool);
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

        
        camera_object.Set_Camera(&win, &swap);
        
        Cbuffer.createCommandBuffers(Fbuffer.swapChainFramebuffers,swap.swapChainExtent, uniformBuffer.descriptorSets);
        createSyncObjects();
       
        
        
    }
    void Renderer::recreateSwapChain()
    {
        int width = 0, height = 0;
        glfwGetFramebufferSize(win->window, &width, &height);
        while (width == 0 || height == 0) {
            glfwGetFramebufferSize(win->window, &width, &height);
            glfwWaitEvents();
        }
        vkDeviceWaitIdle(setup.device);

        cleanupSwapChain();

        swap.createSwapChain();
        swap.createImageViews();
        renderpass.createRenderPass(setup.device, swap.swapChainImageFormat);
        gpipeline.createGraphicsPipeline(swap.swapChainExtent, renderpass.renderPass,uniformBuffer.descriptorSetLayout);
        lightpipeline.createGraphicsPipeline(swap.swapChainExtent, renderpass.renderPass,uniformBuffer.descriptorSetLayout);
        Dbuffer.createDepthResources(swap.swapChainExtent);
        Fbuffer.createFramebuffers(&setup, &swap, &Dbuffer, &renderpass);
        
        if(meshes.size() != 0)
        {
            uniformBuffer.createUniformBuffer();
            uniformBuffer.createDescriptorPool();
            uniformBuffer.createDescriptorSets();
        }
       
        Cbuffer.createCommandBuffers(Fbuffer.swapChainFramebuffers,swap.swapChainExtent, uniformBuffer.descriptorSets);
        

    }
    void Renderer::cleanupSwapChain()
    {
        
        vkDestroyImageView(setup.device, Dbuffer.depthImageView, nullptr);
        vmaDestroyImage(memory_alloc.allocator, Dbuffer.depthImage, Dbuffer.depthImageAllocation);
        for (auto framebuffer : Fbuffer.swapChainFramebuffers) {
            vkDestroyFramebuffer(setup.device, framebuffer, nullptr);
        }

        vkFreeCommandBuffers(setup.device, Cbuffer.commandPool, static_cast<uint32_t>(Cbuffer.commandBuffers.size()), Cbuffer.commandBuffers.data());

        gpipeline.destroyPipeline();
        lightpipeline.destroyPipeline();
        vkDestroyRenderPass(setup.device, renderpass.renderPass, nullptr);

        swap.destroySwap();
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
            uniformBuffer.updateUniformBuffer(i, camera_object);
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

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || win->framebufferResized) {
            win->framebufferResized = false;
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