#define GLM_ENABLE_EXPERIMENTAL
#include "algorithms.h"
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <math.h>
#include <vector>

static constexpr float EPSILON = std::numeric_limits<float>::epsilon();

glm::vec4 algorithms::plane_from_points(const glm::vec3 p1, const glm::vec3 p2, const glm::vec3 p3) {
    glm::vec3 v1 = p1 - p2;
    glm::vec3 v2 = p3 - p2;

    glm::vec3 normal = glm::normalize(glm::cross(v1, v2));
    float k = -1 * (p1.x * normal.x + p1.y * normal.y + p1.z * normal.z);

    std::cout << glm::to_string(glm::vec4(normal, k)) << std::endl;

    return glm::vec4(normal, k);
};

bool algorithms::all_points_on_plane(const glm::vec4 plane, const std::vector<glm::vec3> points) {
    for (auto const point : points) {
        float x = std::abs(plane.x * point.x + plane.y * point.y + plane.z * point.z + plane.w);

        if (x > 0.01) {
            std::cout << glm::to_string(point) + " not on plane" << std::endl;
            return false;
        }
    }

    std::cout << "All points on single plane" << std::endl;
    return true;
}

glm::vec2 algorithms::project_2D(const glm::vec4 plane, const glm::vec3 point) {
}

std::vector<glm::vec2> algorithms::project_2D(const glm::vec4 plane, const std::vector<glm::vec3> points) {
}