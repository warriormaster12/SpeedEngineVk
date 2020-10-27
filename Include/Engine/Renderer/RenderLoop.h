#pragma once 

#include <iostream> 
#include "Vulkan/VulkanRenderer.h"

enum class API 
{
    Vulkan, 
    OpenGl,
};

class RenderLoop
{
public: 
    void initLoop();
    void updateLoop(double deltaTime);
    void destroyLoop();
    Renderer::Vulkan vulkan_api;
private: 
    API apis = API::Vulkan;
};