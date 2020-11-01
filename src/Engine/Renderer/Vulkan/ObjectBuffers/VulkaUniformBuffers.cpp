#include "Engine/Renderer/Vulkan/ObjectBuffers/VulkanUniformBuffers.h"

namespace Renderer
{
    void VulkanUniformBuffer::initBuffer(VulkanMemoryAllocator& vulkanMemoryAllocator)
    {
        p_vulkanMemoryAllocator = &vulkanMemoryAllocator;
    }
    std::vector <VkBuffer> VulkanUniformBuffer::createBuffer(uint32_t byte_size, uint32_t size)
    {
        Buffers.resize(size);
        VkBufferCreateInfo UniformBufferInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
        UniformBufferInfo.size = byte_size;
        UniformBufferInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
        
        VmaAllocationCreateInfo allocInfo = {};
        allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
    
        
        bufferAllocation.resize(size);

        for (size_t i = 0; i < size; i++) {
            vmaCreateBuffer(p_vulkanMemoryAllocator->allocator, &UniformBufferInfo, &allocInfo, &Buffers[i], &bufferAllocation[i], nullptr);
        }
        return Buffers;
    }
    void VulkanUniformBuffer::destroyBuffer()
    {
        for(int i = 0; i < Buffers.size(); i++)
        {
            vmaDestroyBuffer(p_vulkanMemoryAllocator->allocator, Buffers[i], bufferAllocation[i]);
        }
        
    }
    
}