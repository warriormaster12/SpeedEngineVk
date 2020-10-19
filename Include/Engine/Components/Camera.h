#pragma once 

#include "../Renderer/VkIncludes.h"
#include "../Math/Math3D.h"
#include "../Window/Window.h"


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
        

        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);   
       


        void Set_Camera(AppWindow **win);
        void CameraUpdate(float aspect, double DeltaT);
        Camera();
        void processMouse(double xpos, double ypos);

        double lastX{800.0f / 2.0};
        double lastY{600.0 / 2.0};
    private: 
        void processMovement(double DeltaT);
        

        float yaw{0.0f};	
        float pitch{0.0f};
        
    };
}

