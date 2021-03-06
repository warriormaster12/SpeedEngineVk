#pragma once 

#include "VkIncludes.h"
#include "Buffers/VkVertexbuffers.h"
#include "Buffers/VkIndexbuffers.h"


namespace VkRenderer
{
 
    class ModelLoader
    {
    public: 
        std::string MODEL_PATH = "EngineAssets/Models/viking_room.obj";
        

        void loadModel();
        VkindexBuffer *indexBuffer_ref;
        VkvertexBuffer *vertexBuffer_ref;
        
    };
}