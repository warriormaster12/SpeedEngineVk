#include "../Include/Engine/Renderer/VkRenderer.h"
#include "../Include/Engine/Window/Window.h"
#include "../Include/Engine/Components/Mesh.h"


class Engine 
{
public: 
    void run()
    {
        renderer_ref.win_ref = &glfw_win_ref;
        glfw_win_ref.initWindow();
        glfwSetFramebufferSizeCallback(glfw_win_ref.window, framebufferResizeCallback);
        renderer_ref.InitVulkan(glfw_win_ref.window);
        mainLoop();
        cleanup();
    }
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto app = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window));
        app->renderer_ref.framebufferResized = true;
    }
    

private: 
    VkRenderer::Renderer renderer_ref;
    AppWindow glfw_win_ref;
    
   
    
    void mainLoop()
    {
        while (!glfwWindowShouldClose(glfw_win_ref.window))
        {
            glfwPollEvents();
            renderer_ref.drawFrame(glfw_win_ref.window);
        }
        vkDeviceWaitIdle(renderer_ref.setup_ref.device);
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

