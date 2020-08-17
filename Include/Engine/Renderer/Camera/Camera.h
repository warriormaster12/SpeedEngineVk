#pragma once 

#include "../VkIncludes.h"
#include "../../Math/Math3D.h"

namespace VkRenderer
{
    class Camera
    {
    public: 
        Transform3D camera_transform;

        struct
        {
            glm::mat4 perspective;
            glm::mat4 view;
        } matrices;
        
        float fov = 90.0f;
	    float znear = 0.1f, zfar=100.0f;
        float camera_speed = 1.0f;
        glm::vec3 position;


        void Set_Camera(float aspect);
        void CameraUpdate(double DeltaT);
        Camera();
    };
}

