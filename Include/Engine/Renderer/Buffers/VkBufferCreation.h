#pragma once 

#include "../VkIncludes.h"
#include "../VkSetup.h"





namespace VkRenderer
{
    class VkbufferCreation
    {
    public:     

        VkCommandBuffer beginSingleTimeCommands(VkCommandPool& commandPool);
        void endSingleTimeCommands(VkCommandBuffer commandBuffer, VkCommandPool& commandPool);

        VkSetup *setup_ref;
        
    };
}