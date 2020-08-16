#include "Engine/Renderer/VkMemoryManager.h"

namespace VkRenderer
{
    uint32_t VulkanAllocation::nextLocation(vk::DeviceSize offset){
 
        uint32_t tmp = 0;
    
        for(uint32_t i = 0; i < location.size(); i++)
            if(location[i].offset >= offset && location[i].offset < location[tmp].offset) tmp = i;
    
        return tmp;
    }
    
    VulkanAllocation::~VulkanAllocation(){
    
        if(buffer){
            device_.destroyBuffer(buffer);
        }
        if(memory){
            device_.freeMemory(memory); 
            
        }
    
    }
    
    void VulkanAllocation::setBuffer(vk::BufferUsageFlags usage, vk::DeviceSize size){
    
        vk::BufferCreateInfo buffInfo = vk::BufferCreateInfo()
            .setSize(size)
            .setUsage(usage);
    
        buffer = device_.createBuffer(buffInfo);
    
        vk::MemoryRequirements mem = device_.getBufferMemoryRequirements(buffer);
    
        size_ = mem.size;
        location.push_back({size_,0,nullptr});
        alignment = mem.alignment;
    
        vk::MemoryAllocateInfo mallocInfo = vk::MemoryAllocateInfo()
            .setAllocationSize(mem.size)
            .setMemoryTypeIndex(findProperties(memoryInfo_, mem.memoryTypeBits, type_));
    
        memory = device_.allocateMemory(mallocInfo);
    
        device_.bindBufferMemory(buffer, memory, 0);
    
        zeroHandle = device_.mapMemory(memory, 0, mem.size);
    
    }
    
    int32_t VulkanAllocation::newLocation(vk::DeviceSize bytes){
    
        vk::DeviceSize offset = 0;
        uint32_t loc = nextLocation(offset);
    
        while(location[loc].offset - offset < bytes){
    
            offset = location[loc].offset + location[loc].range + (alignment - location[loc].range % alignment);
            loc = nextLocation(offset);
        }
    
        if(!unboundLocation.empty()){
            uint32_t index = unboundLocation.top();
            unboundLocation.pop();
    
            location[index] = {offset, bytes, static_cast<char*>(zeroHandle) + offset};
            return index;
        }
        else{
            location.push_back({offset, bytes, static_cast<char*>(zeroHandle) + offset});
            return location.size() - 1;
        }
    
        return -1;
    }
    
    void VulkanAllocation::eraseLocation(uint32_t loc){
    
        location[loc].offset = size_;
        unboundLocation.push(loc);
    
    }
    
    void VulkanAllocation::defragment(){
    
        void *tmp;
    
        vk::DeviceSize offset = 0;
        uint32_t loc = nextLocation(offset);
    
        for(uint32_t i = 0; i < location.size() - unboundLocation.size() - 1; i++){
    
            if(location[loc].offset - offset > 0){
                
                tmp = location[loc].handle;
                location[loc].offset = offset;
                location[loc].handle = static_cast<char*>(zeroHandle) + offset;
                std::memcpy(location[loc].handle, tmp, static_cast<uint32_t>(location[loc].range));
    
            }
    
            offset = location[loc].offset + location[loc].range + (alignment - location[loc].range % alignment);
            loc = nextLocation(offset);
    
        }
    
    }
    
    int32_t VulkanAllocation::findProperties(vk::PhysicalDeviceMemoryProperties *pMemoryProperties,uint32_t memoryTypeBitsRequirement,vk::MemoryPropertyFlags requiredProperties)
        {
        const uint32_t memoryCount = pMemoryProperties->memoryTypeCount;
    
        for(uint32_t memoryIndex = 0; memoryIndex < memoryCount; ++memoryIndex){
            const uint32_t memoryTypeBits = (1 << memoryIndex);
            const bool isRequiredMemoryType = memoryTypeBitsRequirement & memoryTypeBits;
    
            const vk::MemoryPropertyFlags properties = pMemoryProperties->memoryTypes[memoryIndex].propertyFlags;
            const bool hasRequiredProperties = (properties & requiredProperties) == requiredProperties;
    
            if(isRequiredMemoryType && hasRequiredProperties){
                return static_cast<int32_t>(memoryIndex);
            }
        }
    
        return -1;
    }
}