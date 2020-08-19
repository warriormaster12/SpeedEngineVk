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
        float movement_speed = 1.0f;
        AppWindow **win_ref;
        

        glm::vec3 cameraFront = glm::vec3(0.0f, -1.0f, 0.0f);
        glm::vec3 cameraUp    = glm::vec3(0.0f, 0.0f,  1.0f);   
       


        void Set_Camera(float aspect);
        void CameraUpdate(double DeltaT);
        Camera();
        void processMouse(double xpos, double ypos);
    private: 
        void processMovement(double DeltaT);
        

        bool firstMouse{true};
        float yaw{-90.0f};	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
        float pitch{0.0f};
        float lastX{800.0f / 2.0};
        float lastY{600.0 / 2.0};
    };
}

