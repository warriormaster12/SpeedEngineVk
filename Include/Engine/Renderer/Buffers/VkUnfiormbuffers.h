#pragma once 

#include "../VkIncludes.h"
#include "../VkSetup.h"
#include "../VkMemory.h"
#include "VkBufferCreation.h"
#include "../Camera/Camera.h"
#include "../../Components/Mesh.h"



namespace VkRenderer
{
    struct Light{
        glm::vec4 position;

        glm::vec4 ambient;
        glm::vec4 diffuse;
        glm::vec4 specular;
        glm::vec4 light_color;

        glm::vec4 radius;
    };
    struct UniformBufferObject {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
        glm::vec4 camPos;
        std::array <Light, 2> lights;
        
    };
    
    class VkuniformBuffer
    {
    public: 
        void createDescriptorSetLayout();
        void createDescriptorPool();
        void createDescriptorSets();
        void createUniformBuffer();
        void updateUniformBuffer(uint32_t DescriptorSetIndex, VkExtent2D& swapChainExtent);

        VkDescriptorSetLayout descriptorSetLayout;
        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;
        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;

        std::vector<VkBuffer> uniformLights;
        std::vector<VkDeviceMemory> uniformLightsMemory;

        

        VkSetup *setup_ref;
        VkMemory *memory_ref;
        VkbufferCreation *buffer_ref;
        std::vector <Mesh*> meshes;
        Camera camera_object;
    private: 
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        inline VkDescriptorPoolSize descriptorPoolSize(VkDescriptorType type,uint32_t descriptorCount);
        inline VkDescriptorPoolCreateInfo descriptorPoolCreateInfo(const std::vector<VkDescriptorPoolSize>& poolSizes,uint32_t maxSets);
        inline VkWriteDescriptorSet writeDescriptorSet(VkDescriptorSet dstSet, VkDescriptorType type, uint32_t binding, VkDescriptorImageInfo *imageInfo, VkDescriptorBufferInfo *bufferInfo, uint32_t descriptorCount);
        inline VkDescriptorSetLayoutBinding descriptorSetLayoutBinding(VkDescriptorType type,VkShaderStageFlags stageFlags,uint32_t binding,uint32_t descriptorCount);
        inline VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo(const std::vector<VkDescriptorSetLayoutBinding>& bindings);
    };
}