#pragma once 

#include "../VkIncludes.h"
#include "../VkSetup.h"
#include "../VkMemory.h"




namespace VkRenderer
{
    class VkBufferCreation
    {
    public:     
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        void copyBuffer(VkCommandPool& commandPool, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        VkCommandBuffer beginSingleTimeCommands(VkCommandPool& commandPool);
        void endSingleTimeCommands(VkCommandBuffer commandBuffer, VkCommandPool& commandPool);

        VkSetup *setup_ref;
        VkMemory *memory_ref;
        
    };
}