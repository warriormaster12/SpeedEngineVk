#include "Engine/Components/Scene.h"

namespace Renderer
{
    void Scene::initScene(Vulkan& vulkan_api, AppWindow& win)
    {
        p_vulkan_api = &vulkan_api;
        mesh.initMesh(vulkan_api);
        camera.Set_Camera(win, mesh);
    }
    void Scene::updateScene(double deltaTime)
    {
        mesh.drawMesh(deltaTime);
        camera.CameraUpdate(deltaTime, p_vulkan_api->vulkanImages.vulkanSwapChain.swapChainExtent.width / (float) p_vulkan_api->vulkanImages.vulkanSwapChain.swapChainExtent.height);
    }
    void Scene::destroyScene()
    {
        mesh.destroyMesh();
    }
}