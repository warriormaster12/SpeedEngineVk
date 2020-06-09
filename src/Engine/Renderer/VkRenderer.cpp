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
        
        
    }
    
    void Renderer::DestroyVulkan()
    {  
        vkDestroyDevice(setup_ref.device, nullptr);
         if (enableValidationLayers) {
            setup_ref.DestroyDebugUtilsMessengerEXT(setup_ref.debugMessenger, nullptr);
        }
        vkDestroySurfaceKHR(setup_ref.instance, swap_ref.surface, nullptr);
        vkDestroyInstance(setup_ref.instance, nullptr);
    }
}