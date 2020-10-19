#pragma once 
#include "../Renderer/VkIncludes.h"
#include "../Renderer/VkModelLoader.h"
#include "../Renderer/VkSetup.h"
#include "../Renderer/Buffers/VkVertexbuffers.h"
#include "../Renderer/Buffers/VkIndexbuffers.h"
#include "../Renderer/Buffers/VkBufferCreation.h"
#include "../Math/Math3D.h"
#include "Textures.h"






namespace VkRenderer
{
    enum class mesh_types{user_mesh, preview, skybox};
    class Mesh 
    {
    public: 
        ModelLoader model;
        VkvertexBuffer vertexBuffer;
        VkindexBuffer indexBuffer;  

        
        VkSetup *setup_ref;
        
        Transform3D mesh_transform;
        Texture2D DiffuseTexture;
        Texture2D NormalTexture;
        CubeMapTexture cube_map;
        mesh_types current_mesh_type = mesh_types::user_mesh;
        
        void InitMesh(VkSetup* setup, VkMemoryAllocator* memory_alloc, VkImageManager* image_m, VkCommandPool& commandPool);
        void update(uint32_t imageIndex);
        void DestroyMesh();
    };

}