#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <glm/glm.hpp>
#include <vector>

namespace algorithms {
    glm::vec3 centroid(std::vector<glm::vec3> vertices);
    glm::vec4 plane_from_points(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
    bool all_points_on_plane(const glm::vec4 plane, std::vector<glm::vec3> points);
} // namespace algorithms

#endif