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
        double currentFrame = glfwGetTime();
        lastFrame = currentFrame;
        deltaTime = currentFrame - lastFrame;
        renderLoop.updateLoop(deltaTime);

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

// void Application::mouse_callback(GLFWwindow* window, double xpos, double ypos)
// {
//     renderer.scene.camera.processMouse(xpos, ypos);
// }

// void Application::cursor_enter_callback(GLFWwindow* window, int entered) {
//     if (entered)
//     {
//         glfwGetCursorPos(window, &renderer.scene.camera.lastX, &renderer.scene.camera.lastY);
//     }
// }   



