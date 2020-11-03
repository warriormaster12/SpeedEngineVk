#include "Engine/Renderer/RenderLoop.h"

void RenderLoop::initLoop(AppWindow& win)
{
    //After initializing selected API, the program draws all of the objects
    if(apis == API::Vulkan)
    {
        vulkan_api.initVulkan(win);
        scene.initScene(vulkan_api, win);
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
        scene.updateScene(deltaTime);
        vulkan_api.updateVulkan(scene.mesh.ubo, sizeof(scene.mesh.ubo));
        
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
        scene.destroyScene();
        vulkan_api.destroyVulkan();
    }
    else
    {
        
    }
}