#include "Engine/Window/Window.h"


 void AppWindow::initWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(WIDTH, HEIGHT, "VulkanEngine", nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);


    //glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void AppWindow::cleanupWindow()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}