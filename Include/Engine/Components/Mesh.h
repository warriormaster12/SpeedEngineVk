#pragma once 

#include "../Renderer/Vulkan/VulkanRenderer.h"

namespace Renderer
{
    class Mesh
    {
    public:
        void initMesh(Vulkan& vulkan_api);
        void drawMesh();
        void destroyMesh();

        size_t vertex_attributes = 1;

        std::string model_path = "EngineAssets/Models/cube.obj";
        std::vector <std::string> shaders = {"EngineAssets/Shaders/light_cube_vert.vert","EngineAssets/Shaders/light_cube_frag.frag"};
    private:
        Vulkan *p_vulkan_api;
    };
}