#include "Engine/Components/Camera.h"

namespace Renderer
{
    Camera::Camera()
    {
        camera_transform.translate = glm::vec3(0.0f, 0.0f, 0.0f);
    }
    void Camera::Set_Camera(AppWindow& win, Mesh& mesh)
    {
        win_ref = &win;   
        p_mesh = &mesh;
    }

    void Camera::CameraUpdate(double deltaTime, float aspect)
    {
        matrices.view = glm::lookAt(camera_transform.translate, camera_transform.translate + cameraFront, cameraUp);

        matrices.projection = glm::perspective(glm::radians(fov), aspect, znear, zfar);
        matrices.projection[1][1] *= -1.0f;

        p_mesh->ubo.view = matrices.view;
        p_mesh->ubo.projection = matrices.projection;
        processMovement(deltaTime);
    }
    void Camera::processMovement(double deltaTime)
    {
        float camera_speed = movement_speed * deltaTime;
        if (glfwGetKey(win_ref->window, GLFW_KEY_W) == GLFW_PRESS)
        {
            camera_transform.translate += camera_speed * cameraFront;
        }
        if (glfwGetKey(win_ref->window, GLFW_KEY_S) == GLFW_PRESS)
        {
            camera_transform.translate -= camera_speed * cameraFront;
        }
        if (glfwGetKey(win_ref->window, GLFW_KEY_A) == GLFW_PRESS)
        {
            camera_transform.translate -= glm::normalize(glm::cross(cameraFront, cameraUp)) * camera_speed;
        }
        if (glfwGetKey(win_ref->window, GLFW_KEY_D) == GLFW_PRESS)
        {
            camera_transform.translate+= glm::normalize(glm::cross(cameraFront, cameraUp)) * camera_speed;
        }
        if (glfwGetKey(win_ref->window, GLFW_KEY_E) == GLFW_PRESS)
        {
            camera_transform.translate += camera_speed * cameraUp;
        }
        if (glfwGetKey(win_ref->window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            camera_transform.translate -= camera_speed * cameraUp;
        }

        if (glfwGetKey(win_ref->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            movement_speed = 2.0f;
        }
        else
        {
            movement_speed = 1.0f;
        }
        
    }

    void Camera::processMouse(double xpos, double ypos)
    {
        

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;

        

        float sensitivity = 0.1f; // change this value to your liking
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);

    }
}
