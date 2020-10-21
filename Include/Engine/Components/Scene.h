#pragma once 

#include "../Renderer/VkIncludes.h"
#include "Mesh.h"
#include "Camera.h"




struct Scene 
{
    void initScene(VkRenderer::VkSetup* setup, VkMemoryAllocator* memory_alloc, VkRenderer::VkImageManager* image_m, VkCommandPool& commandPool);
    void updateScene(double DeltaT);
    void destroyScene();

    VkRenderer::Camera camera; 
    std::vector<VkRenderer::Mesh> meshes;
};