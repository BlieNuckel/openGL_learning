#ifndef CAMERA_MOVEMENT_H
#define CAMERA_MOVEMENT_H

#include <algorithm>
#include <glm/glm.hpp>
#include <math.h>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

glm::mat4 lookAtCustom(glm::vec3 position, glm::vec3 target, glm::vec3 up) {
    glm::vec3 cameraDirection = glm::normalize(position - target);
    glm::vec3 cameraRight = glm::normalize(glm::cross(glm::normalize(up), cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

    glm::mat4 positionMat(1.0f);
    positionMat = glm::translate(positionMat, -1.0f * position);

    glm::mat4 lookAtMat(
        cameraRight.x, cameraRight.y, cameraRight.z, 0,
        cameraUp.x, cameraUp.y, cameraUp.z, 0,
        cameraDirection.x, cameraDirection.y, cameraDirection.z, 0,
        0, 0, 0, 1);

    return lookAtMat * positionMat;
}

#endif