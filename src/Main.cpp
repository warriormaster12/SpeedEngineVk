#include "../Include/Engine/Renderer/VkRenderer.h"
#include "../Include/Engine/Window/Window.h"
#include "../Include/Engine/Components/Mesh.h"
#include "../Include/Engine/Config/EngineConf.h"



void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void cursor_enter_callback(GLFWwindow* window, int entered);
VkRenderer::Renderer renderer_ref;
AppWindow glfw_win_ref;
FileConf renderer_config;
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
    glfw_win_ref.WIDTH = std::stoi(settings_array[0]);
    glfw_win_ref.HEIGHT = std::stoi(settings_array[1]);
    glfw_win_ref.initWindow(std::stoi(settings_array[2]));
    
    renderer_ref.Cbuffer_ref.push_const.Unlit = std::stoi(settings_array[3]);

    renderer_ref.win_ref = &glfw_win_ref;
    glfwSetCursorEnterCallback(glfw_win_ref.window, cursor_enter_callback);
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
    
void cursor_enter_callback(GLFWwindow* window, int entered) {
    if (entered)
    {
        glfwGetCursorPos(window, &renderer_ref.uniformBuffer_ref.camera_object.lastX, &renderer_ref.uniformBuffer_ref.camera_object.lastY);
    }
}   

 
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    renderer_ref.uniformBuffer_ref.camera_object.processMouse(xpos, ypos);
}

