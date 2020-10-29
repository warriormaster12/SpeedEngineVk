#pragma once 

#include "../VulkanIncludes.h"
#include "../VulkanDevices.h"
#include "../VulkanGraphicsPipeline.h"
#include "../VulkanImages.h"






namespace Renderer
{
    class VulkanCommandBuffer
    {
    public: 
        VkCommandPool commandPool;
        void createCommandPool(VulkanDevices& vulkanDevices, VulkanImages& vulkanImages);
        void createCommandBuffers(std::vector<VkDescriptorSet>& descriptorSets);
        std::vector<VkCommandBuffer> commandBuffers;

        PushConstants push_const;
    private: 
        VulkanDevices* p_vulkanDevices;
        VulkanImages* p_vulkanImages;
    };
}