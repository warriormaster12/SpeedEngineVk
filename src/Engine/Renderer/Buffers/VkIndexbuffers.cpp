#include "Engine/Renderer/Buffers/VkIndexbuffers.h"

namespace VkRenderer
{
    void VkindexBuffer::createIndexBuffer(VkCommandPool& commandPool)
    {
        VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        buffer_ref->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(setup_ref->device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, indices.data(), (size_t) bufferSize);
        vkUnmapMemory(setup_ref->device, stagingBufferMemory);

        buffer_ref->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

        buffer_ref->copyBuffer(commandPool, stagingBuffer, indexBuffer, bufferSize);

        vkDestroyBuffer(setup_ref->device, stagingBuffer, nullptr);
        vkFreeMemory(setup_ref->device, stagingBufferMemory, nullptr);       
    }
}