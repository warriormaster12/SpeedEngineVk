#include "Engine/Window/Window.h"

void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto app = reinterpret_cast<AppWindow*>(glfwGetWindowUserPointer(window));
    app->framebufferResized = true;
}

 void AppWindow::initWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    set_window_mode();

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    

}

void AppWindow::set_window_mode()
{
    if(window_modes == window_mode::fullscreen)
    {
        get_resolution();
        window = glfwCreateWindow(WIDTH, HEIGHT, "SpeedEngineVk", glfwGetPrimaryMonitor(), nullptr);
    }
    else if (window_modes == window_mode::windowed)
    {
       window = glfwCreateWindow(WIDTH, HEIGHT, "SpeedEngineVk", nullptr, nullptr); 
    }
}

void AppWindow::cleanupWindow()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void AppWindow::get_resolution()
{
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    WIDTH = mode->width;
    HEIGHT = mode->height;
}



