#include "Engine/Renderer/Vulkan/VulkanMemoryAllocator.h"

namespace Renderer
{
    void VulkanMemoryAllocator::createAllocator(VulkanDevices& vulkanDevices)
    {
        VmaAllocatorCreateInfo allocatorInfo = {};
        allocatorInfo.physicalDevice = vulkanDevices.physicalDevice;
        allocatorInfo.device = vulkanDevices.device;
        allocatorInfo.instance = vulkanDevices.instance;
        if(vmaCreateAllocator(&allocatorInfo, &allocator) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create allocator. ");
        }

    }
    void VulkanMemoryAllocator::destroyAllocator()
    {
        vmaDestroyAllocator(allocator);
    }
}
