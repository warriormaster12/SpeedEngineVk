#pragma once 

#include "VkIncludes.h"


namespace VkRenderer
{
    struct UniformBufferObject {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    };

    class VkGPipeline
    {
    public: 
        void createDescriptorSetLayout(VkDevice device);
        void createGraphicsPipeline(VkDevice device, VkExtent2D swapChainExtent);
        VkDescriptorSetLayout descriptorSetLayout;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;
        void createRenderPass(VkFormat swapChainImageFormat, VkDevice device, VkPhysicalDevice physicalDevice);
        VkRenderPass renderPass;
    };
}