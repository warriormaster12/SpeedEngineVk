#include "Engine/Window/Window.h"
#include "Engine/Renderer/VkRenderer.h"


 void AppWindow::initWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(WIDTH, HEIGHT, "VulkanEngine", nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
}

void AppWindow::cleanupWindow()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}


