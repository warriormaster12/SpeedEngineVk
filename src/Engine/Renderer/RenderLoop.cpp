#include "Engine/Renderer/RenderLoop.h"

void RenderLoop::initLoop(AppWindow& win)
{
    //After initializing selected API, the program draws all of the objects
    if(apis == API::Vulkan)
    {
        vulkan_api.initVulkan(win);
        mesh.camera.Set_Camera(win, vulkan_api.vulkanImages.vulkanSwapChain.swapChainExtent.width / (float) vulkan_api.vulkanImages.vulkanSwapChain.swapChainExtent.height);
        mesh.initMesh(vulkan_api);
        
    }
    else
    {
        
    }
    
}

void RenderLoop::updateLoop()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    //The program redraws all of the objects here
    if(apis == API::Vulkan)
    {   
        mesh.drawMesh(deltaTime);
        vulkan_api.updateVulkan(mesh.ubo, sizeof(mesh.ubo));
        
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