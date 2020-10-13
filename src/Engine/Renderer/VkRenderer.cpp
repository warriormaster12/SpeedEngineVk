#include "Engine/Renderer/VkRenderer.h"


namespace VkRenderer
{
    Renderer::Renderer()
    {

        //GraphicsPipeline
        gpipeline_ref.setup_ref = &vkobjects.setup;
        lightpipeline_ref.setup_ref = &vkobjects.setup;

        //RenderPass
        renderpass_ref.Dbuffer_ref = &Dbuffer_ref;

        //UniformBuffer
        vkobjects.uniformBuffer.camera_object.win_ref = &win_ref;
        
        //BufferCreation
        buffer_ref.setup_ref = &vkobjects.setup;
        
        

        //CommandBuffer
        vkobjects.Cbuffer.setup_ref = &vkobjects.setup;
        vkobjects.Cbuffer.gpipeline_ref = &gpipeline_ref;
        vkobjects.Cbuffer.lightpipeline_ref = &lightpipeline_ref;
        vkobjects.Cbuffer.renderpass_ref = &renderpass_ref;
        
        //DepthBuffer
        Dbuffer_ref.setup_ref = &vkobjects.setup;
        Dbuffer_ref.image_m_ref = &image_m_ref;

        //imageManager
        image_m_ref.setup_ref = &vkobjects.setup;
        image_m_ref.buffer_ref = &buffer_ref;
        image_m_ref.memory_alloc_ref = &memory_alloc;
    }
    
    void Renderer::InitVulkan()
    {
        
        vkobjects.setup.Initialize();
        vkobjects.swap.Initialize(&vkobjects.setup, win_ref, &image_m_ref);
        vkobjects.setup.createLogicalDevice(vkobjects.swap.surface);
        memory_alloc.createAllocator(vkobjects.setup);
        vkobjects.swap.createSwapChain();
        vkobjects.swap.createImageViews();
        renderpass_ref.createRenderPass(vkobjects.setup.device, vkobjects.swap.swapChainImageFormat);
        vkobjects.uniformBuffer.Initialize(&vkobjects.setup, &memory_alloc);
        gpipeline_ref.shaders = {"EngineAssets/Shaders/Model_vert.vert", "EngineAssets/Shaders/Model_frag.frag",};
        gpipeline_ref.createGraphicsPipeline(vkobjects.swap.swapChainExtent, renderpass_ref.renderPass,vkobjects.uniformBuffer.descriptorSetLayout);
        lightpipeline_ref.shaders = {"EngineAssets/Shaders/light_cube_vert.vert", "EngineAssets/Shaders/light_cube_frag.frag",};
        lightpipeline_ref.vertex_attributes = 1; 
        lightpipeline_ref.createGraphicsPipeline(vkobjects.swap.swapChainExtent, renderpass_ref.renderPass,vkobjects.uniformBuffer.descriptorSetLayout);
        vkobjects.Cbuffer.createCommandPool(vkobjects.swap.surface);
        Dbuffer_ref.createDepthResources(vkobjects.swap.swapChainExtent);
        Fbuffer_ref.createFramebuffers(&vkobjects, &Dbuffer_ref, &renderpass_ref);
    
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
                meshes[i].InitMesh(&vkobjects.setup, &memory_alloc, &image_m_ref,vkobjects.Cbuffer.commandPool);
                vkobjects.uniformBuffer.meshes.push_back(&meshes[i]);
                vkobjects.Cbuffer.meshes.push_back(&meshes[i]);
            }
        
            
            
            vkobjects.uniformBuffer.createUniformBuffer(); 
            
            vkobjects.uniformBuffer.createDescriptorPool();
            vkobjects.uniformBuffer.createDescriptorSets();

            

            meshes[0].mesh_transform.translate=glm::vec3(4.0f,0.0f,-2.0f);
            meshes[0].mesh_transform.rotation=glm::vec3(-90.0f,0.0f,-90.0f);
            
            meshes[1].mesh_transform.rotation=glm::vec3(-90.0f,0.0f,90.0f);
            meshes[1].mesh_transform.translate=glm::vec3(4.0f,0.0f,2.0f);

            meshes[2].mesh_transform.translate=glm::vec3(8.0f,0.0f,0.0f);
            meshes[2].mesh_transform.scale = glm::vec3(0.002f);
            meshes[2].mesh_transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
            meshes[3].mesh_transform.scale = glm::vec3(0.1);
            
        }     

        
        
        
        vkobjects.Cbuffer.createCommandBuffers(Fbuffer_ref.swapChainFramebuffers,vkobjects.swap.swapChainExtent, vkobjects.uniformBuffer.descriptorSets);
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
        vkDeviceWaitIdle(vkobjects.setup.device);

        cleanupSwapChain();

        vkobjects.swap.createSwapChain();
        vkobjects.swap.createImageViews();
        renderpass_ref.createRenderPass(vkobjects.setup.device, vkobjects.swap.swapChainImageFormat);
        gpipeline_ref.createGraphicsPipeline(vkobjects.swap.swapChainExtent, renderpass_ref.renderPass,vkobjects.uniformBuffer.descriptorSetLayout);
        lightpipeline_ref.createGraphicsPipeline(vkobjects.swap.swapChainExtent, renderpass_ref.renderPass,vkobjects.uniformBuffer.descriptorSetLayout);
        Dbuffer_ref.createDepthResources(vkobjects.swap.swapChainExtent);
        Fbuffer_ref.createFramebuffers(&vkobjects, &Dbuffer_ref, &renderpass_ref);
        
        if(meshes.size() != 0)
        {
            vkobjects.uniformBuffer.createUniformBuffer();
            vkobjects.uniformBuffer.createDescriptorPool();
            vkobjects.uniformBuffer.createDescriptorSets();
        }
       
        vkobjects.Cbuffer.createCommandBuffers(Fbuffer_ref.swapChainFramebuffers,vkobjects.swap.swapChainExtent, vkobjects.uniformBuffer.descriptorSets);
        

    }
    void Renderer::cleanupSwapChain()
    {
        
        vkDestroyImageView(vkobjects.setup.device, Dbuffer_ref.depthImageView, nullptr);
        vmaDestroyImage(memory_alloc.allocator, Dbuffer_ref.depthImage, Dbuffer_ref.depthImageAllocation);
        for (auto framebuffer : Fbuffer_ref.swapChainFramebuffers) {
            vkDestroyFramebuffer(vkobjects.setup.device, framebuffer, nullptr);
        }

        vkFreeCommandBuffers(vkobjects.setup.device, vkobjects.Cbuffer.commandPool, static_cast<uint32_t>(vkobjects.Cbuffer.commandBuffers.size()), vkobjects.Cbuffer.commandBuffers.data());

        vkDestroyPipeline(vkobjects.setup.device, gpipeline_ref.graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(vkobjects.setup.device, gpipeline_ref.pipelineLayout, nullptr);
        vkDestroyPipeline(vkobjects.setup.device, lightpipeline_ref.graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(vkobjects.setup.device, lightpipeline_ref.pipelineLayout, nullptr);
        vkDestroyRenderPass(vkobjects.setup.device, renderpass_ref.renderPass, nullptr);

        for (auto imageView : vkobjects.swap.swapChainImageViews) {
            vkDestroyImageView(vkobjects.setup.device, imageView, nullptr);
        }

        vkDestroySwapchainKHR(vkobjects.setup.device, vkobjects.swap.swapChain, nullptr);
        vkobjects.uniformBuffer.DestroyUniformBuffer();
        vkDestroyDescriptorPool(vkobjects.setup.device, vkobjects.uniformBuffer.descriptorPool, nullptr);
    }
    void Renderer::DestroyVulkan()
    {  
        cleanupSwapChain();
        
        
        

        vkDestroyDescriptorSetLayout(vkobjects.setup.device, vkobjects.uniformBuffer.descriptorSetLayout, nullptr);  
        for (int i=meshes.size()-1; i >= 0; i--)
        {
            meshes[i].DestroyMesh();
        }
        

        
        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroySemaphore(vkobjects.setup.device, renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(vkobjects.setup.device, imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(vkobjects.setup.device, inFlightFences[i], nullptr);
        }
        vkDestroyCommandPool(vkobjects.setup.device, vkobjects.Cbuffer.commandPool, nullptr);
        
        vmaDestroyAllocator(memory_alloc.allocator);
        vkDestroyDevice(vkobjects.setup.device, nullptr);
        if (enableValidationLayers) {
            vkobjects.setup.DestroyDebugUtilsMessengerEXT(vkobjects.setup.debugMessenger, nullptr);
        }
        vkDestroySurfaceKHR(vkobjects.setup.instance, vkobjects.swap.surface, nullptr);
        vkDestroyInstance(vkobjects.setup.instance, nullptr);
        
        
    }


     void Renderer::drawFrame()
    {
        vkWaitForFences(vkobjects.setup.device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(vkobjects.setup.device, vkobjects.swap.swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);
        
        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            recreateSwapChain();
            return;
        } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }
        
        for (int i=0; i < meshes.size(); i++)
        {
            vkobjects.uniformBuffer.updateUniformBuffer(i, vkobjects.swap.swapChainExtent);
        }

        

        if (imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
            vkWaitForFences(vkobjects.setup.device, 1, &imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
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
        submitInfo.pCommandBuffers = &vkobjects.Cbuffer.commandBuffers[imageIndex];

        VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        vkResetFences(vkobjects.setup.device, 1, &inFlightFences[currentFrame]);

        if (vkQueueSubmit(vkobjects.setup.graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = {vkobjects.swap.swapChain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        result = vkQueuePresentKHR(vkobjects.setup.presentQueue, &presentInfo);

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
        imagesInFlight.resize(vkobjects.swap.swapChainImages.size(), VK_NULL_HANDLE);

        VkSemaphoreCreateInfo semaphoreInfo{};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            if (vkCreateSemaphore(vkobjects.setup.device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
                vkCreateSemaphore(vkobjects.setup.device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
                vkCreateFence(vkobjects.setup.device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create synchronization objects for a frame!");
            }
        }
    }
}