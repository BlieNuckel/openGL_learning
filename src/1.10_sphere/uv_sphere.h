using namespace std;
#include <glm/glm.hpp>
#include <math.h>
#include <mesh.h>
#include <numbers>
#include <vector>

Mesh uv_sphere(int n_slices, int n_stacks) {
    Mesh mesh;

    glm::vec3 northPole = glm::vec3(0.0f, 1.0f, 0.0f);
    mesh.add_vertex(northPole);

    for (size_t i = 0; i < n_stacks; i++) {
        double phi = 2.0 * numbers::pi * double(i + 1) / double(n_stacks);
        for (size_t j = 0; j < n_slices; j++) {
            double theta = 2.0 * numbers::pi * double(j) / double(n_slices);
            double x = sin(phi) * cos(theta);
            double y = cos(phi);
            double z = sin(phi) * sin(theta);

            mesh.add_vertex(glm::vec3(float(x), float(y), float(z)));
        }
    }

    glm::vec3 southPole = glm::vec3(0.0f, -1.0f, 0.0f);
    mesh.add_vertex(southPole);

    return mesh;
}