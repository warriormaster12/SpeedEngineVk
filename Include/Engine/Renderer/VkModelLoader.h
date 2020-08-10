#pragma once 

#include "VkIncludes.h"
#include "Buffers/VkVertexbuffers.h"
#include "Buffers/VkIndexbuffers.h"
#include "../Components/Mesh.h"

namespace VkRenderer
{
 
    class ModelLoader
    {
    public: 
        const std::string MODEL_PATH = "EngineAssets/Models/viking_room.obj";
        const std::string TEXTURE_PATH = "EngineAssets/Textures/viking_room.png";

        void loadModel();
        VkindexBuffer *Ibuffer_ref;
        VkVbuffer *Vbuffer_ref;

        uint32_t startIndex = 0;
        uint32_t numIndices = 0;
        uint32_t startInstance = 0;

        glm::vec3 pos;
        
    };
}