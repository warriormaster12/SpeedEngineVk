#include "../Include/Engine/Renderer/VkRenderer.h"
#include "../Include/Engine/Window/Window.h"
#include "../Include/Engine/Components/Mesh.h"


void mouse_callback(GLFWwindow* window, double xpos, double ypos);
VkRenderer::Renderer renderer_ref;
AppWindow glfw_win_ref;
window_mode mode;


void cleanup()
{
    renderer_ref.DestroyVulkan();
    glfw_win_ref.cleanupWindow();
}
void mainLoop()
{
    while (!glfwWindowShouldClose(glfw_win_ref.window))
    {
        glfwPollEvents();
        renderer_ref.drawFrame();

        if(glfwGetKey(glfw_win_ref.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(glfw_win_ref.window, true);
        }
    }
    vkDeviceWaitIdle(renderer_ref.setup_ref.device);
}

void run()
{
    

    glfw_win_ref.initWindow(mode.fullscreen);
    renderer_ref.win_ref = &glfw_win_ref;
    glfwSetCursorPosCallback(glfw_win_ref.window, mouse_callback);
    renderer_ref.InitVulkan();
    mainLoop();
    cleanup();

    
}

int main()
{
    try {
        run();
    } catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
    
    

 
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    renderer_ref.Ubuffer_ref.camera_object.processMouse(xpos, ypos);
}

