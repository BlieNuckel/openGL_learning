#include <algorithms/algorithms.h>
#include <vector>

int main() {
    std::vector<glm::vec3> points = {
        glm::vec3(1.0f, 1.0f, 20.0f),
        glm::vec3(3.0f, 5.0f, 1.0f),
        glm::vec3(-1.0f, 20.0f, -10.0f)
    };

    glm::vec4 plane = algorithms::plane_from_points(points[0], points[1], points[2]);
    bool valid = algorithms::all_points_on_plane(plane, points);
}