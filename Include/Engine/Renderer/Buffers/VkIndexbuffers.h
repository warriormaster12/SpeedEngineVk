#pragma once

#include "../VkIncludes.h"
#include "../VkSetup.h"
#include "VkBufferCreation.h"
#include "../VkMemory.h"

namespace VkRenderer
{
    

    class VkindexBuffer
    {
    public: 
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;
        std::vector<uint32_t> indices;

        void createIndexBuffer(VkCommandPool& commandPool);

        VkSetup *setup_ref;
        VkbufferCreation *buffer_ref;
    };
}