#include "Engine/Renderer/VkMemoryAllocator.h"


void VkMemoryAllocator::createAllocator(VkRenderer::VkSetup& setup_ref)
{
    VmaAllocatorCreateInfo allocatorInfo = {};
    allocatorInfo.physicalDevice = setup_ref.physicalDevice;
    allocatorInfo.device = setup_ref.device;
    allocatorInfo.instance = setup_ref.instance;
    if(vmaCreateAllocator(&allocatorInfo, &allocator) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create allocator. ");
    }

}