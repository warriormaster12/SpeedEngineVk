#include "Engine/Renderer/Camera/Camera.h"

namespace VkRenderer
{
    Camera::Camera()
    {
        camera_transform.translate = glm::vec3(3.0f, 0.0f, 1.0f);
    }
    void Camera::Set_Camera(float aspect)
    {
        
        matrices.view = glm::lookAt(camera_transform.translate, camera_transform.translate + cameraFront, cameraUp);; 

        matrices.perspective = glm::perspective(glm::radians(fov), aspect, znear, zfar);
		matrices.perspective[1][1] *= -1.0f;
    }

    void Camera::CameraUpdate(double DeltaT)
    {
      
        
       camera_speed = 0.05f * DeltaT;
       ///if (glfwGetKey(win_ref->window, GLFW_KEY_W) == GLFW_PRESS)
       
        camera_transform.translate += camera_speed * cameraFront;
           
       
        

    }
}
