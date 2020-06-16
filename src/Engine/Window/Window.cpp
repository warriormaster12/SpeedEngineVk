#include "Engine/Window/Window.h"
#include "Engine/Renderer/VkRenderer.h"


 void AppWindow::initWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(WIDTH, HEIGHT, "VulkanEngine", nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);


    
}

void AppWindow::cleanupWindow()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void AppWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    VkRenderer::Renderer renderer_ref;
    glfwGetWindowUserPointer(window);
    renderer_ref.framebufferResized = true;
}
