#pragma once 

#include "Window/Window.h"
#include "Renderer/VkRenderer.h"
#include "Config/EngineConf.h"

class Application 
{
public: 
    VkRenderer::Renderer renderer;
    AppWindow win;

    void InitApplication();
    void UpdateApplication();
    void DestroyApplication();

    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void cursor_enter_callback(GLFWwindow* window, int entered);

private:
    FileConf renderer_config;
    window_mode mode;
};