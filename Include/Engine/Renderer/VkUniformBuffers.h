#pragma once 

#include "VkIncludes.h"

namespace VkRenderer
{
    class VkUBuffer
    {
    public: 
        
        void createDescriptorPool(VkDevice device, std::vector<VkImage> swapChainImages);
        void createDescriptorSets(VkDescriptorSetLayout descriptorSetLayout, std::vector<VkImage> swapChainImages, VkDevice device, std::vector<VkBuffer> uniformBuffers);
        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;
    };
}