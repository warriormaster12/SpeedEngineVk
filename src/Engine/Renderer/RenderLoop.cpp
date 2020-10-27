#include "Engine/Renderer/RenderLoop.h"

void RenderLoop::initLoop(AppWindow& win)
{
    if(apis == API::Vulkan)
    {
        vulkan_api.initVulkan(win);
    }
    else
    {
        
    }
    
}

void RenderLoop::updateLoop(double deltaTime)
{
    if(apis == API::Vulkan)
    {
        vulkan_api.updateVulkan(deltaTime);
    }
    else
    {
        
    }
}

void RenderLoop::destroyLoop()
{
    if(apis == API::Vulkan)
    {
        vulkan_api.destroyVulkan();
    }
    else
    {
        
    }
}