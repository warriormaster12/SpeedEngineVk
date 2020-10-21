#include "Engine/Components/Scene.h"

void Scene::initScene(VkRenderer::VkSetup* setup, VkMemoryAllocator* memory_alloc, VkRenderer::VkImageManager* image_m, VkCommandPool& commandPool)
{
    meshes.emplace_back();
    meshes.emplace_back();
    meshes.emplace_back();
    meshes.emplace_back();

    meshes[2].DiffuseTexture.TEXTURE_PATH = "EngineAssets/Textures/chapel_diffuse.tga";
    meshes[2].NormalTexture.TEXTURE_PATH = "EngineAssets/Textures/chapel_normal.tga";
    meshes[2].model.MODEL_PATH = "EngineAssets/Models/chapel_obj.obj";
    meshes[3].model.MODEL_PATH = "EngineAssets/Models/cube.obj";
    meshes[3].current_mesh_type = VkRenderer::mesh_types::preview;

    for (int i = 0; i < meshes.size(); i++) {
        meshes[i].InitMesh(setup, memory_alloc, image_m,commandPool);
    }      
}

void Scene::updateScene(double DeltaT)
{
    meshes[0].mesh_transform.translate=glm::vec3(4.0f,0.0f,-2.0f);
    meshes[0].mesh_transform.rotation=glm::vec3(-90.0f,0.0f,-90.0f);
    
    meshes[1].mesh_transform.rotation=glm::vec3(-90.0f,0.0f,90.0f);
    meshes[1].mesh_transform.translate=glm::vec3(4.0f,0.0f,2.0f);

    meshes[2].mesh_transform.translate=glm::vec3(8.0f,0.0f,0.0f);
    meshes[2].mesh_transform.scale = glm::vec3(0.002f);
    meshes[2].mesh_transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    meshes[3].mesh_transform.scale = glm::vec3(0.1);
}

void Scene::destroyScene()
{
    for (int i=meshes.size()-1; i >= 0; i--)
    {
        meshes[i].DestroyMesh();
    }
}