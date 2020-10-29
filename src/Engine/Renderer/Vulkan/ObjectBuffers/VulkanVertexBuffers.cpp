#include "Engine/Renderer/Vulkan/ObjectBuffers/VulkanVertexBuffers.h"

namespace Renderer
{
    void VulkanVertexBuffer::createVertexBuffer(VulkanMemoryAllocator& vulkanMemoryAllocator)
    {
             

        VkBufferCreateInfo bufferInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
        bufferInfo.size = sizeof(vertices[0]) * vertices.size();
        bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;

        VmaAllocationCreateInfo allocInfo = {};
        allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;

        VkBuffer stagingBuffer;
        vmaCreateBuffer(vulkanMemoryAllocator.allocator, &bufferInfo, &allocInfo, &stagingBuffer, &allocation, nullptr);

        void* data;
        vmaMapMemory(vulkanMemoryAllocator.allocator, allocation, &data);
            memcpy(data, vertices.data(), (size_t) bufferInfo.size);
        vmaUnmapMemory(vulkanMemoryAllocator.allocator, allocation);

        bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        vmaDestroyBuffer(vulkanMemoryAllocator.allocator, stagingBuffer, allocation);
        vmaCreateBuffer(vulkanMemoryAllocator.allocator, &bufferInfo, &allocInfo, &vertexBuffer, &allocation, nullptr);
        

    }

    void VulkanVertexBuffer::destroyVertexBuffer(VulkanMemoryAllocator& vulkanMemoryAllocator)
    {
        vmaDestroyBuffer(vulkanMemoryAllocator.allocator, vertexBuffer, allocation);
    }
}