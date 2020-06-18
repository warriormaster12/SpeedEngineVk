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
        void createDescriptorSetLayout(VkSetup& setup_ref);
        void createDescriptorPool(VkSetup& setup_ref, std::vector<VkImage> swapChainImages);
        void createDescriptorSets(VkSetup& setup_ref, std::vector<VkImage> swapChainImages);
        void createUniformBuffers(std::vector<VkImage> swapChainImages, VkBufferCreation& buffer_ref, VkSetup& setup_ref, VkMemory& memory_ref);
        void updateUniformBuffer(uint32_t currentImage, VkExtent2D& swapChainExtent, VkSetup& setup_ref);

        VkDescriptorSetLayout descriptorSetLayout;
        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;
        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;
    };
}