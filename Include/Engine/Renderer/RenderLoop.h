#pragma once 

#include <iostream> 
#include "Vulkan/VulkanRenderer.h"
#include "../Components/Mesh.h"
#include "../Components/Camera.h"

enum class API 
{
    Vulkan, 
    OpenGl,
};

class RenderLoop
{
public: 
    void initLoop(AppWindow& win);
    void updateLoop();
    void destroyLoop();
    Renderer::Vulkan vulkan_api;
    Renderer::Mesh mesh;
    Renderer::Camera camera;
private: 
    API apis = API::Vulkan;
    double deltaTime = 0;
    double lastFrame = 0;
};