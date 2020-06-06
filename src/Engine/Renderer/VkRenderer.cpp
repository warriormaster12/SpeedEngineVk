#include "Engine/Renderer/VkRenderer.h"
#include "Engine/Renderer/VkGraphicsPipeline.h"
#include "Engine/Renderer/VkMemory.h"
#include "Engine/Renderer/VkUniformBuffers.h"
#include "Engine/Renderer/VkTextureManager.h"
#include "Engine/Renderer/VkDepthBuffer.h"


namespace VkRenderer
{
    VkMemory memory_ref;
    VkGPipeline pipeline_ref;
    VkUBuffer Ubuffer_ref;
    VkTextureManager texture_ref;
    VkDepthBuffer DBuffer_ref;
    void Renderer::InitVulkan()
    {
        createInstance();
        checkValidationLayerSupport();
        setupDebugMessenger();
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice();
        createSwapChain();
        createImageViews();
        pipeline_ref.createRenderPass(swapChainImageFormat, device, physicalDevice);
        pipeline_ref.createDescriptorSetLayout(device);
        pipeline_ref.createGraphicsPipeline(device, swapChainExtent);
        createCommandPool();
        createDepthResources();
        createFramebuffers();
        createTextureImage();
        createTextureImageView();
        texture_ref.createTextureSampler(device);
        createVertexBuffer();
        createIndexBuffer();
        createUniformBuffers();
        Ubuffer_ref.createDescriptorPool(device, swapChainImages);
        Ubuffer_ref.createDescriptorSets(pipeline_ref.descriptorSetLayout, swapChainImages, device, textureImageView, texture_ref.textureSampler);
        createCommandBuffers();
        createSyncObjects();
        
    }
    
    void Renderer::DestroyVulkan()
    {  
        cleanupSwapChain();

        vkDestroySampler(device, texture_ref.textureSampler, nullptr);
        vkDestroyImageView(device, textureImageView, nullptr);

        vkDestroyImage(device, textureImage, nullptr);
        vkFreeMemory(device, textureImageMemory, nullptr);

        vkDestroyDescriptorSetLayout(device, pipeline_ref.descriptorSetLayout, nullptr);

        vkDestroyBuffer(device, indexBuffer, nullptr);
        vkFreeMemory(device, memory_ref.indexBufferMemory, nullptr);

        vkDestroyBuffer(device, vertexBuffer, nullptr);
        vkFreeMemory(device, memory_ref.vertexBufferMemory, nullptr);


        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(device, inFlightFences[i], nullptr);
        }

        vkDestroyCommandPool(device, commandPool, nullptr);

        vkDestroyDevice(device, nullptr);

        if (enableValidationLayers) {
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        }

        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);
    }
}