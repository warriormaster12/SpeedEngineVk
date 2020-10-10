#pragma once 

#include "../VkIncludes.h"
#include "../VkSetup.h"
#include "../VkMemoryAllocator.h"

namespace VkRenderer
{
    struct Vertex 
    {
        glm::vec3 pos;
        glm::vec3 color;
        glm::vec2 texCoord;
        glm::vec3 normal;

        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions(size_t amount_of_attributes = 4) {
            std::vector<VkVertexInputAttributeDescription> attributeDescriptions{};
            std::vector<size_t> offsets{offsetof(Vertex, pos), offsetof(Vertex, color), offsetof(Vertex, texCoord), offsetof(Vertex, normal)};
            for(size_t i = 0; i < amount_of_attributes; i++)
            {
                attributeDescriptions.emplace_back();
                attributeDescriptions[i].binding = 0;
                attributeDescriptions[i].location = i;
                attributeDescriptions[i].format = VK_FORMAT_R32G32B32_SFLOAT;
                attributeDescriptions[i].offset = offsets[i];
            }
    
            return attributeDescriptions;
        }
        bool operator==(const Vertex& other) const {
            return pos == other.pos && color == other.color && texCoord == other.texCoord && normal == other.normal;
        }
    };

    
    
    class VkvertexBuffer
    {
    public: 
        void createVertexBuffer();
        VkBuffer vertexBuffer;
        VkSetup *setup_ref;
        VkMemoryAllocator *memory_alloc_ref;
        VmaAllocation allocation;
        std::vector<Vertex> vertices;
    };
}