#include "Engine/ApplicationLoop.h"

void Application::InitApplication()
{
    std::vector <std::string> text_test = 
    {
        "[Renderer]",
        "r.window_width = 1920", 
        "r.window_height = 1080",
        "r.window_fullscreen = 1",
        "r.unlit = 0"
    };
    renderer_config.generateFile("renderer.conf",text_test);
    std::vector <std::string> settings_array = renderer_config.readFile("renderer.conf");
    for(int i = 0; i < settings_array.size(); i++)
    {
        std::cout<<settings_array[i]<<std::endl;
    }

    win.WIDTH = std::stoi(settings_array[0]);
    win.HEIGHT = std::stoi(settings_array[1]);
    win.initWindow(std::stoi(settings_array[2]));

    renderer.Cbuffer.push_const.Unlit = std::stoi(settings_array[3]);
    renderer.win = &win;
    
    renderer.InitVulkan();
}

void Application::UpdateApplication()
{
    while (!glfwWindowShouldClose(win.window))
    {
        glfwPollEvents();
        renderer.drawFrame();

        if(glfwGetKey(win.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(win.window, true);
        }
    }
    vkDeviceWaitIdle(renderer.setup.device);
    DestroyApplication();
}

void Application::DestroyApplication()
{
    renderer.DestroyVulkan();
    win.cleanupWindow();
}

void Application::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    renderer.scene.camera.processMouse(xpos, ypos);
}

void Application::cursor_enter_callback(GLFWwindow* window, int entered) {
    if (entered)
    {
        glfwGetCursorPos(window, &renderer.scene.camera.lastX, &renderer.scene.camera.lastY);
    }
}   



