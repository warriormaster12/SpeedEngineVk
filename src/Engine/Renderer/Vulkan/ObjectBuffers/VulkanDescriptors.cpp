#include "Engine/Renderer/Vulkan/ObjectBuffers/VulkanDescriptors.h"

namespace Renderer
{
    void VulkanDescriptors::createDescriptorSetLayout(VulkanDevices& vulkanDevices, uint32_t descriptor_size)
    {
        p_vulkanDevices = &vulkanDevices;
        d_size = descriptor_size;
        std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings = {
            descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, 1),
        };

        VkDescriptorSetLayoutCreateInfo descriptorLayout = descriptorSetLayoutCreateInfo(setLayoutBindings);

        if (vkCreateDescriptorSetLayout(vulkanDevices.device, &descriptorLayout, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor set layout!");
        }
    }

    void VulkanDescriptors::createDescriptorPool()
    {
         std::vector<VkDescriptorPoolSize> poolSizes = {
            descriptorPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, d_size),
        };
        VkDescriptorPoolCreateInfo descriptorPoolInfo = descriptorPoolCreateInfo(poolSizes, d_size);
        if (vkCreateDescriptorPool(p_vulkanDevices->device, &descriptorPoolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor pool!");
        }   
    }

    void VulkanDescriptors::createDescriptorSets(std::vector<VkBuffer> inputBuffer, uint32_t byte_size)
    {
        descriptorSets.resize(d_size);
        for (size_t i = 0; i < descriptorSets.size(); i++) {
            std::vector<VkDescriptorSetLayout> layouts(descriptorSets.size(), descriptorSetLayout);
            VkDescriptorSetAllocateInfo allocInfo{};
            allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
            allocInfo.descriptorPool = descriptorPool;
            allocInfo.descriptorSetCount = static_cast<uint32_t>(1);
            allocInfo.pSetLayouts = layouts.data();

            
            if (vkAllocateDescriptorSets(p_vulkanDevices->device, &allocInfo, &descriptorSets[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to allocate descriptor sets!");
            }

        
            VkDescriptorBufferInfo bufferInfo{};
            bufferInfo.buffer = inputBuffer[i];
            bufferInfo.offset = 0;
            bufferInfo.range = byte_size;

            // VkDescriptorImageInfo DiffuseImageInfo{};
            // DiffuseImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            // DiffuseImageInfo.imageView = scene_ref->meshes[i].DiffuseTexture.textureImageView;
            // DiffuseImageInfo.sampler = scene_ref->meshes[i].DiffuseTexture.textureSampler;

            
            std::vector<VkWriteDescriptorSet> descriptorWrites = {
                writeDescriptorSet(descriptorSets[i], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 0, nullptr, &bufferInfo, 1),
            };
           

            vkUpdateDescriptorSets(p_vulkanDevices->device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
        }
    }

    
    
    inline VkDescriptorSetLayoutBinding VulkanDescriptors::descriptorSetLayoutBinding(VkDescriptorType type,VkShaderStageFlags stageFlags,uint32_t binding,uint32_t descriptorCount)
    {
        VkDescriptorSetLayoutBinding setLayoutBinding {};
        setLayoutBinding.descriptorType = type;
        setLayoutBinding.stageFlags = stageFlags;
        setLayoutBinding.binding = binding;
        setLayoutBinding.descriptorCount = descriptorCount;
        return setLayoutBinding;
    }
    
    inline VkDescriptorSetLayoutCreateInfo VulkanDescriptors::descriptorSetLayoutCreateInfo(const std::vector<VkDescriptorSetLayoutBinding>& bindings)
    {
        VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{};
        descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        descriptorSetLayoutCreateInfo.pBindings = bindings.data();
        descriptorSetLayoutCreateInfo.bindingCount = static_cast<uint32_t>(bindings.size());
        return descriptorSetLayoutCreateInfo;
    }


    inline VkDescriptorPoolCreateInfo VulkanDescriptors::descriptorPoolCreateInfo(const std::vector<VkDescriptorPoolSize>& poolSizes,uint32_t maxSets)
    {
        VkDescriptorPoolCreateInfo descriptorPoolInfo{};
        descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        descriptorPoolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
        descriptorPoolInfo.pPoolSizes = poolSizes.data();
        descriptorPoolInfo.maxSets = maxSets;
        return descriptorPoolInfo;
    }

    inline VkDescriptorPoolSize VulkanDescriptors::descriptorPoolSize(VkDescriptorType type,uint32_t descriptorCount)
    {
        VkDescriptorPoolSize descriptorPoolSize {};
        descriptorPoolSize.type = type;
        descriptorPoolSize.descriptorCount = descriptorCount;
        return descriptorPoolSize;
    }

    inline VkWriteDescriptorSet VulkanDescriptors::writeDescriptorSet(VkDescriptorSet dstSet, VkDescriptorType type, uint32_t binding, VkDescriptorImageInfo *imageInfo, VkDescriptorBufferInfo *bufferInfo, uint32_t descriptorCount)
    {
        VkWriteDescriptorSet writeDescriptorSet {};
        writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writeDescriptorSet.dstSet = dstSet;
        writeDescriptorSet.descriptorType = type;
        writeDescriptorSet.dstBinding = binding;
        writeDescriptorSet.pImageInfo = imageInfo;
        writeDescriptorSet.pBufferInfo = bufferInfo;
        writeDescriptorSet.descriptorCount = descriptorCount;
        return writeDescriptorSet;
    }
}