#include "Engine/Renderer/Buffers/VkIndexbuffers.h"

namespace VkRenderer
{
    void VkindexBuffer::createIndexBuffer()
    {
        VkBufferCreateInfo bufferInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
        bufferInfo.size = sizeof(indices[0]) * indices.size();
        bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        VmaAllocationCreateInfo allocInfo = {};
        allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;

        VkBuffer stagingBuffer;
        vmaCreateBuffer(memory_alloc_ref->allocator, &bufferInfo, &allocInfo, &stagingBuffer, &allocation, nullptr);

        void* data;
        vmaMapMemory(memory_alloc_ref->allocator, allocation, &data);
            memcpy(data, indices.data(), (size_t) bufferInfo.size);
        vmaUnmapMemory(memory_alloc_ref->allocator, allocation);

        bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        vmaDestroyBuffer(memory_alloc_ref->allocator, stagingBuffer, allocation);
        vmaCreateBuffer(memory_alloc_ref->allocator, &bufferInfo, &allocInfo, &indexBuffer, &allocation, nullptr);     
    }
}