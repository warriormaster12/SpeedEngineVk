#include "Engine/Renderer/VkRenderer.h"
#include "Engine/Renderer/VkGraphicsPipeline.h"
#include "Engine/Renderer/VkMemory.h"


namespace VkRenderer
{
    VkMemory memory_ref;
    VkGPipeline pipeline_ref;
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
        pipeline_ref.createRenderPass(swapChainImageFormat, device);
        pipeline_ref.createDescriptorSetLayout(device);
        pipeline_ref.createGraphicsPipeline(device, swapChainExtent);
        createFramebuffers();
        createCommandPool();
        createVertexBuffer();
        createIndexBuffer();
        createUniformBuffers();
        createDescriptorPool();
        createDescriptorSets(pipeline_ref.descriptorSetLayout);
        createCommandBuffers();
        createSyncObjects();
        
    }
    
    void Renderer::DestroyVulkan()
    {  
        cleanupSwapChain();

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