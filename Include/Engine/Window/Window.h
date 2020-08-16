#pragma once 

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

 struct window_mode
{
    int windowed = 0;
    int fullscreen = 1; 
    int borderless = 2;
};

class AppWindow
{
public: 
    GLFWwindow* window;
    unsigned int WIDTH =1280;
    unsigned int HEIGHT = 720;
   

    void initWindow(int window_mode);
    void cleanupWindow();
    void get_resolution();
    void set_window_mode(int window_mode);

    

    bool framebufferResized = false;
    
};