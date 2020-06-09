#include "../Include/Engine/Renderer/VkRenderer.h"
#include "../Include/Engine/Window/Window.h"

class Engine 
{
public: 
    void run()
    {
        glfw_win_ref.initWindow();
        renderer_ref.InitVulkan(glfw_win_ref.window);
        mainLoop();
        cleanup();
    }
    

private: 
    VkRenderer::Renderer renderer_ref;
    AppWindow glfw_win_ref;
   
    //static void framebufferResizeCallback(GLFWwindow* window, int width, int height)
    //{
    //    auto app = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window));
    //    app->renderer_ref.framebufferResized = true; 
    //}
    void mainLoop()
    {
        while (!glfwWindowShouldClose(glfw_win_ref.window))
        {
            glfwPollEvents();
            //renderer_ref.drawFrame();
        }
        //vkDeviceWaitIdle(renderer_ref.device);
    }
    void cleanup()
    {
        renderer_ref.DestroyVulkan();
        glfw_win_ref.cleanupWindow();
    }
};

int main()
{
    Engine engine_ref; 
    try {
        engine_ref.run();
    } catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

