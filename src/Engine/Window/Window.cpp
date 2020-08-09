#include "Engine/Window/Window.h"
#include "Engine/Renderer/VkRenderer.h"

void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto app = reinterpret_cast<AppWindow*>(glfwGetWindowUserPointer(window));
    app->framebufferResized = true;
}

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



