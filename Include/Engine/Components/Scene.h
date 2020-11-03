#pragma once 

#include "Mesh.h"
#include "Camera.h"

namespace Renderer
{
    class Scene
    {
    public: 
        void initScene(Vulkan& vulkan_api, AppWindow& win);
        void updateScene(double deltaTime);
        void destroyScene();

        Mesh mesh;
        Camera camera;
    private: 
        Vulkan* p_vulkan_api;
    };
}