#pragma once 
#include "../Renderer/VkIncludes.h"


struct Transform3D
{
    glm::vec3 translate;
    glm::vec3 scale;
    glm::vec3 rotation;
};