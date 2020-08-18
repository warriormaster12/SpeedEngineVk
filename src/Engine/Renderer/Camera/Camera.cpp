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

    void Camera::CameraUpdate(double DeltaT, GLFWwindow *window)
    {
       processMovement(DeltaT, window);

       
    }
    void Camera::processMovement(double DeltaT, GLFWwindow *window)
    {
        float camera_speed = movement_speed * DeltaT;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            camera_transform.translate += camera_speed * cameraFront;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            camera_transform.translate -= camera_speed * cameraFront;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            camera_transform.translate -= glm::normalize(glm::cross(cameraFront, cameraUp)) * camera_speed;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            camera_transform.translate+= glm::normalize(glm::cross(cameraFront, cameraUp)) * camera_speed;
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        {
            camera_transform.translate += camera_speed * cameraUp;
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            camera_transform.translate -= camera_speed * cameraUp;
        }
    }
}
