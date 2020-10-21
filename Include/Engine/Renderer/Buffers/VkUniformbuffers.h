#pragma once 

#include "../VkIncludes.h"
#include "../VkSetup.h"
#include "../VkMemoryAllocator.h"
#include "../../Components/Scene.h"
#include "../../Components/Light.h"






namespace VkRenderer
{
    
    struct LightBuffer
    {
        std::array <Point_light, 2> point_lights;
        Spot_light spot_light;
        Directional_light directional_light;
    };

    struct UniformBufferObject {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
        glm::vec4 camPos;
    };
    
    class VkuniformBuffer
    {
    public: 
        void Initialize(VkSetup* setup, VkMemoryAllocator* memory_alloc, Scene* scene);
        void createDescriptorSetLayout();
        void createDescriptorPool();
        void createDescriptorSets();
        void createUniformBuffer();
        void updateUniformBuffer(int DescriptorSetIndex);
        void DestroyUniformBuffer();

        VkDescriptorSetLayout descriptorSetLayout;
        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;
        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkBuffer> lightBuffers;

        VkMemoryAllocator *memory_alloc_ref;
        std::vector <VmaAllocation> uboAllocation;
        std::vector <VmaAllocation> lightAllocation;
        VkSetup *setup_ref;
        Scene *scene_ref;
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