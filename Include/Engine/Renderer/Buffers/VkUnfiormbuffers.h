#pragma once 

#include "../VkIncludes.h"
#include "../VkSetup.h"
#include "../VkSwapChain.h"
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
        void createDescriptorPool();
        void createDescriptorSets();
        void createUniformBuffers(VkBufferCreation& buffer_ref);
        void updateUniformBuffer(uint32_t currentImage);

        VkDescriptorSetLayout descriptorSetLayout;
        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;
        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;

        VkSetup *setup_ref;
        VkSwapChain *swap_ref;
        VkMemory *memory_ref;
    };
}