#include "Engine/Renderer/Buffers/VkVertexbuffers.h"

namespace VkRenderer
{
    void VkVbuffer::createVertexBuffer(VkCommandPool& commandPool)
    {
        VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        buffer_ref->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(setup_ref->device, stagingBufferMemory, 0, bufferSize, 0, &data);
            memcpy(data, vertices.data(), (size_t) bufferSize);
        vkUnmapMemory(setup_ref->device, stagingBufferMemory);

        buffer_ref->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

        buffer_ref->copyBuffer(commandPool, stagingBuffer, vertexBuffer, bufferSize);

        vkDestroyBuffer(setup_ref->device, stagingBuffer, nullptr);
        vkFreeMemory(setup_ref->device, stagingBufferMemory, nullptr);

    }
}