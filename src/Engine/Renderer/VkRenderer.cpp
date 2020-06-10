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
        swap_ref.createSwapChain(setup_ref.physicalDevice, setup_ref.device, setup_ref);
        swap_ref.createImageViews(setup_ref.device);
        gpipeline_ref.createRenderPass(setup_ref.device, swap_ref.swapChainImageFormat);
        gpipeline_ref.createGraphicsPipeline(setup_ref.device, swap_ref.swapChainExtent);
        Fbuffer_ref.createFramebuffers(setup_ref.device, swap_ref.swapChainImageViews, swap_ref.swapChainExtent, gpipeline_ref.renderPass);
        Cbuffer_ref.createCommandPool(setup_ref, swap_ref.surface);
        Cbuffer_ref.createCommandBuffers(setup_ref.device, Fbuffer_ref.swapChainFramebuffers, swap_ref.swapChainExtent, gpipeline_ref);
        draw_ref.createSyncObjects(setup_ref, swap_ref.swapChainImages);
    }
    void Renderer::UpdateVulkan()
    {
        draw_ref.drawFrame(setup_ref,swap_ref.swapChain,Cbuffer_ref.commandBuffers);
    }
    void Renderer::DestroyVulkan()
    {  
        for (size_t i = 0; i < draw_ref.MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroySemaphore(setup_ref.device, draw_ref.renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(setup_ref.device, draw_ref.imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(setup_ref.device, draw_ref.inFlightFences[i], nullptr);
        }
        vkDestroyCommandPool(setup_ref.device, Cbuffer_ref.commandPool, nullptr);
        for (auto framebuffer : Fbuffer_ref.swapChainFramebuffers) {
            vkDestroyFramebuffer(setup_ref.device, framebuffer, nullptr);
        }
        vkDestroyPipeline(setup_ref.device, gpipeline_ref.graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(setup_ref.device, gpipeline_ref.pipelineLayout, nullptr);
        vkDestroyRenderPass(setup_ref.device, gpipeline_ref.renderPass, nullptr);
        for (auto imageView : swap_ref.swapChainImageViews) {
            vkDestroyImageView(setup_ref.device, imageView, nullptr);
        }
        vkDestroySwapchainKHR(setup_ref.device, swap_ref.swapChain, nullptr);
        vkDestroyDevice(setup_ref.device, nullptr);
         if (enableValidationLayers) {
            setup_ref.DestroyDebugUtilsMessengerEXT(setup_ref.debugMessenger, nullptr);
        }
        vkDestroySurfaceKHR(setup_ref.instance, swap_ref.surface, nullptr);
        vkDestroyInstance(setup_ref.instance, nullptr);
    }
}