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
       
        vulkan_api.updateVulkan(deltaTime);
        //mesh.drawMesh();
        vulkan_api.finishUpdate();
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
        vulkan_api.destroyVulkan();
    }
    else
    {
        
    }
}