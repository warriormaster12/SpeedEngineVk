#include "Engine/Renderer/Camera/Camera.h"

namespace VkRenderer
{
    Camera::Camera()
    {
        camera_transform.translate = glm::vec3(2.0f, 2.0f, 2.0f);
        camera_transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    }
    void Camera::Set_Camera(float aspect)
    {
        
        matrices.view = glm::lookAt(camera_transform.translate, camera_transform.rotation, glm::vec3(0.0f, 0.0f, 1.0f));; 

        matrices.perspective = glm::perspective(glm::radians(fov), aspect, znear, zfar);
		matrices.perspective[1][1] *= -1.0f;
    }

    void Camera::CameraUpdate(double DeltaT)
    {

        camera_speed = camera_speed * DeltaT;

    }
}
