#pragma once 

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

enum class window_mode
{
    windowed,
    fullscreen,
};

class AppWindow
{
public: 
    GLFWwindow* window;
    unsigned int WIDTH =1280;
    unsigned int HEIGHT = 720;
    window_mode window_modes= window_mode::windowed;
   

    void initWindow();
    void cleanupWindow();
    void get_resolution();
    void set_window_mode();

    

    bool framebufferResized = false;
    
};