#include "Engine/Renderer/RenderLoop.h"

void RenderLoop::initLoop(AppWindow& win)
{
    //After initializing selected API, the program draws all of the objects
    if(apis == API::Vulkan)
    {
        vulkan_api.initVulkan(win);
        mesh.initMesh(vulkan_api);
        
    }
    else
    {
        
    }
    
}

void RenderLoop::updateLoop(double deltaTime)
{
    //The program redraws all of the objects here
    if(apis == API::Vulkan)
    {   
        vulkan_api.updateVulkan();
        mesh.drawMesh(vulkan_api.imageIndex, deltaTime);
    }
    else
    {
        
    }
}

void RenderLoop::destroyLoop()
{
    //The program destroyes everything before closing
    if(apis == API::Vulkan)
    {
        vkDeviceWaitIdle(vulkan_api.vulkanDevices.device);
        mesh.destroyMesh();
        vulkan_api.destroyVulkan();
    }
    else
    {
        
    }
}