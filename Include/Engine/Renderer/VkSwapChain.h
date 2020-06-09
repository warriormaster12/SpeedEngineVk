#pragma once 

#include "VkIncludes.h"


namespace VkRenderer
{
    class VkSwapChain
    {
    public:

        VkSurfaceKHR surface;
        void createSurface(GLFWwindow *window, VkInstance instance);

    };
}