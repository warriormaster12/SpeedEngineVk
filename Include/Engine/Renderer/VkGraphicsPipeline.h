#pragma once 

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <optional>
#include <set>
#include <algorithm>
#include <fstream>
#include <array>


namespace VkRenderer
{

    class VkGPipeline
    {
    public: 
        void createGraphicsPipeline(VkDevice device, VkExtent2D swapChainExtent);
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;
        void createRenderPass(VkFormat swapChainImageFormat, VkDevice device);
        VkRenderPass renderPass;
    };
}