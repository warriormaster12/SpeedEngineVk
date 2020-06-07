#pragma once 

#include "VkIncludes.h"

namespace VkRenderer
{
    class VkUBuffer
    {
    public: 
        
        void createDescriptorPool(VkDevice device, std::vector<VkImage> swapChainImages);
        void updateUniformBuffer(uint32_t currentImage, VkExtent2D swapChainExtent, VkDevice device, GLFWwindow *window);
        void createDescriptorSets(VkDescriptorSetLayout descriptorSetLayout, std::vector<VkImage> swapChainImages, VkDevice device, VkImageView textureImageView, VkSampler textureSampler);
        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;
        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;
        
        glm::vec3 Pos{ glm::vec3(0.0f, 0.0f, 1.0f) };
        glm::vec3 Front{ glm::vec3(0.0f, 0.0f, -1.0f) };
        glm::vec3 Up{ glm::vec3(0.0f, 1.0f, 0.0f) };

        //Temp
        void ProcessInput(GLFWwindow *window);
        // timing
        float deltaTime = 0.0f;	// time between current frame and last frame
        float lastFrame = 0.0f;
    };
}