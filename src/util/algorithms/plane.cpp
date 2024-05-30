#include "algorithms.h"
#include <glm/glm.hpp>s
#include <math.h>

glm::vec4 algorithms::plane_from_points(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
    glm::vec3 v1 = p1 - p2;
    glm::vec3 v2 = p3 - p2;

    glm::vec3 normal = glm::normalize(glm::cross(v1, v2));
    float k = -1 * (p1.x * normal.x + p1.y * normal.y + p1.z * normal.z);

    return glm::vec4(normal, k);
};

bool algorithms::all_points_on_plane(const glm::vec4 plane, std::vector<glm::vec3> points) {
    for (auto const point : points) {
        float x = std::abs(plane.x * point.x + plane.y * point.y + plane.z * point.z + plane.w);

        if (x > 0.0000001) {
            return false;
        }
    }

    return true;
}