#pragma once 

#include "VkIncludes.h"
#include <vulkan/vulkan.hpp>
#include "VkSetup.h"
#include <stack>


namespace VkRenderer
{
    class VulkanAllocation{
 
        vk::PhysicalDeviceMemoryProperties *memoryInfo_;
        vk::DeviceSize alignment = 0, size_ = 0;
        vk::Device device_;

        struct Location{
            vk::DeviceSize offset;
            vk::DeviceSize range;
            void *handle = nullptr;
        };
        

        
    
        void *zeroHandle;
        vk::DeviceMemory memory;
        vk::MemoryPropertyFlags type_;
    
        std::stack<uint32_t> unboundLocation;
    
        uint32_t nextLocation(vk::DeviceSize offset);
 
    public:
 
        VulkanAllocation(){};
        VulkanAllocation(vk::MemoryPropertyFlags type,
            vk::PhysicalDeviceMemoryProperties *memoryInfo, vk::Device device)
            :type_(type), memoryInfo_(memoryInfo), device_(device_){ 
            if(type & vk::MemoryPropertyFlagBits::eDeviceLocal) std::runtime_error("Sorry, this is not meant for device local memory types");
        }
    
        ~VulkanAllocation();
    
        void setBuffer(vk::BufferUsageFlags usage, vk::DeviceSize size);
    
        int32_t newLocation(vk::DeviceSize bytes);
    
        void eraseLocation(uint32_t loc);
    
        void defragment();
    
        vk::Buffer buffer;
    
        std::vector<Location> location;
    
        static int32_t findProperties(
            vk::PhysicalDeviceMemoryProperties *pMemoryProperties,
            uint32_t memoryTypeBitsRequirement,
            vk::MemoryPropertyFlags requiredProperties);
 
    };
}