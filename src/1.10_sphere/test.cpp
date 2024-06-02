#include <algorithms/algorithms.h>
#include <vector>

int main() {
    std::vector<glm::vec3> points = {
        glm::vec3(-2.66f, 0.2f, 7.4f),
        glm::vec3(0.0f, -2.0f, 1.0f),
        glm::vec3(4.0f, -2.0f, -2.0f),
        glm::vec3(4.0f, 1.0f, 4.0f),
        glm::vec3(2.88, 2.39, 7.63),
    };

    glm::vec4 plane = algorithms::plane_from_points(points[0], points[1], points[2]);
    bool valid = algorithms::all_points_on_plane(plane, points);
}