#pragma once 

#include "VkIncludes.h"

namespace VkRenderer
{
    class VkUBuffer
    {
    public: 
        
        void createDescriptorPool(VkDevice device, std::vector<VkImage> swapChainImages);
        void updateUniformBuffer(uint32_t currentImage, VkExtent2D swapChainExtent, VkDevice device);
        void createDescriptorSets(VkDescriptorSetLayout descriptorSetLayout, std::vector<VkImage> swapChainImages, VkDevice device, VkImageView textureImageView, VkSampler textureSampler);
        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;
        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;
        glm::vec3 Pos{ glm::vec3(1.5f, 1.5f, 3.0f) };
    };
}