#pragma once 

#include "../VkIncludes.h"
#include "../VkSetup.h"
#include "../VkMemory.h"
#include "VkBufferCreation.h"



namespace VkRenderer
{
    struct UniformBufferObject {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    };
    class VkUbuffer
    {
    public: 
        void createDescriptorSetLayout();
        void createDescriptorPool(std::vector<VkImage>& swapChainImages);
        void createDescriptorSets(std::vector<VkImage>& swapChainImages, VkImageView& textureImageView, VkSampler& textureSampler);
        void createUniformBuffers( std::vector<VkImage>& swapChainImages);
        void updateUniformBuffer(uint32_t currentImage, VkExtent2D& swapChainExtent);

        VkDescriptorSetLayout descriptorSetLayout;
        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;
        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;

        VkSetup *setup_ref;
        VkMemory *memory_ref;
        VkBufferCreation *buffer_ref;
        
    };
}