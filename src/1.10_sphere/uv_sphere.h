using namespace std;
#include <glm/glm.hpp>
#include <math.h>
#include <mesh.h>
#include <numbers>
#include <vector>

Mesh uv_sphere(int n_slices, int n_stacks) {
    Mesh mesh;

    glm::vec3 northPole = glm::vec3(0.0f, 1.0f, 0.0f);
    int v0 = mesh.add_vertex(northPole);

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
    int v1 = mesh.add_vertex(southPole);

    for (size_t i = 0; i < n_slices; i++) {
        int i0 = i + 1;
        int i1 = (i + 1) % n_slices + 1;
        mesh.add_triangle(glm::vec3(v0, i1, i0));

        i0 = i + n_slices * (n_stacks - 2) + 1;
        i1 = (i + 1) % n_slices + n_slices * (n_stacks - 2) + 1;
        mesh.add_triangle(glm::vec3(v1, i0, i1));
    }

    return mesh;
}