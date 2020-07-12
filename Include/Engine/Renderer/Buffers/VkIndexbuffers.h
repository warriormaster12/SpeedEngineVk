#pragma once

#include "../VkIncludes.h"
#include "../VkSetup.h"
#include "VkBufferCreation.h"
#include "../VkMemory.h"

namespace VkRenderer
{
    const std::vector<uint16_t> indices = {
        0, 1, 2, 2, 3, 0
    };

    class VkindexBuffer
    {
    public: 
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;

        void createIndexBuffer(VkCommandPool& commandPool);

        VkSetup *setup_ref;
        VkBufferCreation *buffer_ref;
    };
}