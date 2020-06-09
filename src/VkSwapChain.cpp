#include "Engine/Renderer/VkSwapChain.h"


namespace VkRenderer
{
   void VkSwapChain::createSurface(GLFWwindow *window, VkInstance instance)
   {
       if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
   } 
}