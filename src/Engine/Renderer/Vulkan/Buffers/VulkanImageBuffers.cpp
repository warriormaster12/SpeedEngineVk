#include "Engine/Renderer/Vulkan/Buffers/VulkanImageBuffers.h"


namespace Renderer
{
    void VulkanImageBuffer::initImageBuffer(VulkanDevices& vulkanDevices)
    {
        p_vulkanDevices = &vulkanDevices;
    }

    VkCommandBuffer VulkanImageBuffer::beginSingleTimeCommands(VkCommandPool& commandPool) {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = commandPool;
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(p_vulkanDevices->device, &allocInfo, &commandBuffer);

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);

        return commandBuffer;
    }
    void  VulkanImageBuffer::endSingleTimeCommands(VkCommandBuffer commandBuffer, VkCommandPool& commandPool) {
        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(p_vulkanDevices->graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(p_vulkanDevices->graphicsQueue);

        vkFreeCommandBuffers(p_vulkanDevices->device, commandPool, 1, &commandBuffer);
    }

}