#ifndef FLY_CAM_H
#define FLY_CAM_H

#include "./camera_utils.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <glm/glm.hpp>
#include <math.h>

const float YAW_FLY = -90.0f;
const float PITCH_FLY = 0.0f;
const float SPEED_FLY = 2.5f;
const float SENSITIVITY_FLY = 0.08f;

class FlyCam {
public:
    glm::vec3 Pos;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;

    FlyCam(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW_FLY, float pitch = PITCH_FLY) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED_FLY), MouseSensitivity(SENSITIVITY_FLY) {
        Pos = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    FlyCam(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED_FLY), MouseSensitivity(SENSITIVITY_FLY) {
        Pos = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    glm::mat4 view() {
        return glm::lookAt(Pos, Pos + Front, Up);
    }

    void ProcessKeyboard(Camera_Movement direction, float deltaTime) {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD) {
            Pos += MovementSpeed * Front * velocity;
        }
        if (direction == BACKWARD) {
            Pos -= MovementSpeed * Front * velocity;
        }
        if (direction == LEFT) {
            Pos -= glm::normalize(glm::cross(Front, Up)) * MovementSpeed * velocity;
        }
        if (direction == RIGHT) {
            Pos += glm::normalize(glm::cross(Front, Up)) * MovementSpeed * velocity;
        }
        if (direction == UP) {
            Pos += Up * MovementSpeed * velocity;
        }
        if (direction == DOWN) {
            Pos -= Up * MovementSpeed * velocity;
        }
    }

    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw = glm::mod(Yaw + xoffset, 360.0f);
        if (constrainPitch) {
            Pitch = std::clamp(Pitch - yoffset, -89.0f, 89.0f);
        } else {
            Pitch = Pitch - yoffset;
        }

        updateCameraVectors();
    }

    void ProcessMouseScroll(float yoffset) {
        MovementSpeed = std::max(MovementSpeed + yoffset, 1.0f);
    }

private:
    void updateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

        Front = glm::normalize(front);
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};

#endif