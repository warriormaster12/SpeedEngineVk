#pragma once 

#include "../VkIncludes.h"
#include "../../Math/Math3D.h"
#include "../../Window/Window.h"


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
        
        float fov = 60.0f;
	    float znear = 0.1f, zfar=100.0f;
        float camera_speed = 1.0f;
        //AppWindow *win_ref;
        

        glm::vec3 cameraFront = glm::vec3(-1.0f, 0.0f, 0.0f);
        glm::vec3 cameraUp    = glm::vec3(0.0f, 0.0f,  1.0f);   
       


        void Set_Camera(float aspect);
        void CameraUpdate();
        Camera();
    private: 
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;
    };
}

