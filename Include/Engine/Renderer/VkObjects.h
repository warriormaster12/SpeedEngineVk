#pragma once 

#include "VkSetup.h"
#include "VkSwapChain.h"
#include "Buffers/VkUniformbuffers.h"
#include "Buffers/VkCommandbuffers.h"

namespace VkRenderer
{
    class VkMasterObject
    {
    public: 
        VkSetup setup;
        VkSwapChain swap;
        VkuniformBuffer uniformBuffer;
        VkcommandBuffer Cbuffer;
    };
}
