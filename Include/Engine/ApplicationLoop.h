#pragma once 

#include "Window/Window.h"
#include "Config/EngineConf.h"
#include "Renderer/RenderLoop.h"

class Application 
{
public:
    AppWindow win;

    void InitApplication();
    void UpdateApplication();
    void DestroyApplication();

    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void cursor_enter_callback(GLFWwindow* window, int entered);

private:
    double deltaTime = 0;
    double lastFrame = 0;
    RenderLoop renderLoop;
    FileConf renderer_config;
    window_mode mode;
};