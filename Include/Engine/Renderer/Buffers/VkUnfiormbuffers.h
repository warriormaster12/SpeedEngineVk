#pragma once 

#include "../VkIncludes.h"
#include "../VkSetup.h"
#include "../VkMemory.h"
#include "VkBufferCreation.h"
#include "../../Components/Mesh.h"



namespace VkRenderer
{
    struct UniformBufferObject {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
        glm::vec3 lightPosition;
    };
    
    class VkUbuffer
    {
    public: 
        void createDescriptorSetLayout();
        void createDescriptorPool();
        void createDescriptorSets(VkImageView& textureImageView, VkSampler& textureSampler);
        void createUniformBuffer();
        void updateUniformBuffer(uint32_t DescriptorSetIndex, VkExtent2D& swapChainExtent);

        VkDescriptorSetLayout descriptorSetLayout;
        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;
        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;

        

        VkSetup *setup_ref;
        VkMemory *memory_ref;
        VkBufferCreation *buffer_ref;
        std::vector <Mesh*> meshes;
    };
}