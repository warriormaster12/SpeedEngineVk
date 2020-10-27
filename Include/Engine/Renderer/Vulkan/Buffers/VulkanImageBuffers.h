#pragma once 

#include "../VulkanIncludes.h"
#include "../VulkanDevices.h"





namespace Renderer
{
    class VulkanImageBuffer
    {
    public:     
        void initImageBuffer(VulkanDevices& vulkanDevices);
        VkCommandBuffer beginSingleTimeCommands(VkCommandPool& commandPool);
        void endSingleTimeCommands(VkCommandBuffer commandBuffer, VkCommandPool& commandPool);
    private:
        VulkanDevices *p_vulkanDevices;
    };
}