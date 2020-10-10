#include "Engine/Renderer/Buffers/VkVertexbuffers.h"

namespace VkRenderer
{
    void VkvertexBuffer::createVertexBuffer()
    {
             

        VkBufferCreateInfo bufferInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
        bufferInfo.size = sizeof(vertices[0]) * vertices.size();
        bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;

        VmaAllocationCreateInfo allocInfo = {};
        allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;

        VkBuffer stagingBuffer;
        vmaCreateBuffer(memory_alloc_ref->allocator, &bufferInfo, &allocInfo, &stagingBuffer, &allocation, nullptr);

        void* data;
        vmaMapMemory(memory_alloc_ref->allocator, allocation, &data);
            memcpy(data, vertices.data(), (size_t) bufferInfo.size);
        vmaUnmapMemory(memory_alloc_ref->allocator, allocation);

        bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        vmaDestroyBuffer(memory_alloc_ref->allocator, stagingBuffer, allocation);
        vmaCreateBuffer(memory_alloc_ref->allocator, &bufferInfo, &allocInfo, &vertexBuffer, &allocation, nullptr);
        

    }
}