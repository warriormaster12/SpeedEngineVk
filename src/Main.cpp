#include "../Include/Engine/Renderer/VkRenderer.h"

class Engine 
{
public: 
    void run()
    {
        initWindow();
        renderer_ref.InitVulkan();
        mainLoop();
        cleanup();
    }
    GLFWwindow* window;
    unsigned int WIDTH =1280;
    unsigned int HEIGHT = 720;
    

private: 
    Renderer renderer_ref;
    void initWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window = glfwCreateWindow(WIDTH, HEIGHT, "VulkanEngine", nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        renderer_ref.window = window; 
        renderer_ref.WIDTH = WIDTH;
        renderer_ref.HEIGHT = HEIGHT;


        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

    }
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height)
    {
        auto app = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window));
        app->renderer_ref.framebufferResized = true; 
    }
    void mainLoop()
    {
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            renderer_ref.drawFrame();
        }
        vkDeviceWaitIdle(renderer_ref.device);
    }
    void cleanup()
    {
        renderer_ref.DestroyVulkan();

        glfwDestroyWindow(window);
        glfwTerminate();
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

