#pragma once 

#include "../VulkanIncludes.h"
#include "../VulkanDevices.h"

namespace Renderer
{
    class VulkanDescriptors
    {
    public: 
        void createDescriptorSetLayout(VulkanDevices& vulkanDevices);
        void createDescriptorPool();
        void createDescriptorSets(); 

        VkDescriptorSetLayout descriptorSetLayout;
        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;
    
    private: 
        inline VkDescriptorPoolSize descriptorPoolSize(VkDescriptorType type,uint32_t descriptorCount);
        inline VkDescriptorPoolCreateInfo descriptorPoolCreateInfo(const std::vector<VkDescriptorPoolSize>& poolSizes,uint32_t maxSets);
        inline VkWriteDescriptorSet writeDescriptorSet(VkDescriptorSet dstSet, VkDescriptorType type, uint32_t binding, VkDescriptorImageInfo *imageInfo, VkDescriptorBufferInfo *bufferInfo, uint32_t descriptorCount);
        inline VkDescriptorSetLayoutBinding descriptorSetLayoutBinding(VkDescriptorType type,VkShaderStageFlags stageFlags,uint32_t binding,uint32_t descriptorCount);
        inline VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo(const std::vector<VkDescriptorSetLayoutBinding>& bindings);
    };
}