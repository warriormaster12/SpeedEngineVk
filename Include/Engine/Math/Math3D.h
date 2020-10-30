#pragma once 
#include "../Renderer/Vulkan/VulkanIncludes.h"


struct Transform3D
{
    glm::vec3 translate;
    glm::vec3 scale;
    glm::vec3 rotation;
};