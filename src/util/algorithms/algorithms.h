#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <glm/glm.hpp>
#include <vector>

namespace algorithms {

    glm::vec3 centroid(const std::vector<glm::vec3> vertices);
    glm::vec4 plane_from_points(const glm::vec3 p1, const glm::vec3 p2, const glm::vec3 p3);
    std::vector<glm::vec2> project_2D(const glm::vec4 plane, const std::vector<glm::vec3> points);
    glm::vec2 project_2D(const glm::vec4 plane, const glm::vec3 point);

    bool all_points_on_plane(const glm::vec4 plane, std::vector<glm::vec3> points);
    bool definitely_greater_than(float a, float b, float epsilon);
} // namespace algorithms

#endif