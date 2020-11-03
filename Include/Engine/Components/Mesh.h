#pragma once 

#include "../Renderer/Vulkan/VulkanRenderer.h"
#include "../Math/Math3D.h"


namespace Renderer
{
    struct UniformBufferObject{
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
    };
    class Mesh
    {
    public:
        void initMesh(Vulkan& vulkan_api);
        void drawMesh(double deltaTime);
        void destroyMesh();

        Transform3D transform;

        size_t vertex_attributes = 1;
        UniformBufferObject ubo{};

        std::string model_path = "EngineAssets/Models/sphere.obj";
        std::vector <std::string> shaders = {"EngineAssets/Shaders/light_cube_vert.vert","EngineAssets/Shaders/light_cube_frag.frag"};
    private:
        Vulkan *p_vulkan_api;
        
    };
}