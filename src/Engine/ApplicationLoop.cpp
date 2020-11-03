#include "Engine/ApplicationLoop.h"

void Application::InitApplication()
{
    win.initWindow();
    renderLoop.initLoop(win);   
}

void Application::UpdateApplication()
{
    while (!glfwWindowShouldClose(win.window))
    {
        
        
        glfwPollEvents();
        renderLoop.updateLoop();

        if(glfwGetKey(win.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(win.window, true);
        }
    }
    DestroyApplication();
}

void Application::DestroyApplication()
{
    renderLoop.destroyLoop();
    win.cleanupWindow();
}

void Application::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    renderLoop.mesh.camera.processMouse(xpos, ypos);
}

void Application::cursor_enter_callback(GLFWwindow* window, int entered) {
    if (entered)
    {
        glfwGetCursorPos(window, &renderLoop.mesh.camera.lastX, &renderLoop.mesh.camera.lastY);
    }
}   



