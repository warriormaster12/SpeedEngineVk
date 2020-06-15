#pragma once 

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>



class AppWindow
{
public: 
    GLFWwindow* window;
    unsigned int WIDTH =1280;
    unsigned int HEIGHT = 720;

    void initWindow();
    void cleanupWindow();
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
    
};