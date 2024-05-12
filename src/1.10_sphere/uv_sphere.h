#ifndef UV_SPHERE_H
#define UV_SPHERE_H

#include <glm/glm.hpp>
#include <math.h>
#include <mesh/mesh.h>
#include <numbers>

Mesh uv_sphere(int n_slices, int n_stacks) {
    Mesh mesh;

    glm::vec3 northPole = glm::vec3(0.0f, 1.0f, 0.0f);
    int v0 = mesh.add_vertex(northPole);

    for (size_t i = 0; i < n_stacks; i++) {
        double phi = 2.0 * std::numbers::pi * double(i + 1) / double(n_stacks);
        for (size_t j = 0; j < n_slices; j++) {
            double theta = 2.0 * std::numbers::pi * double(j) / double(n_slices);
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
        mesh.add_triangle(v0, i1, i0);

        i0 = i + n_slices * (n_stacks - 2) + 1;
        i1 = (i + 1) % n_slices + n_slices * (n_stacks - 2) + 1;
        mesh.add_triangle(v1, i0, i1);
    }

    for (size_t j = 0; j < n_stacks - 2; j++) {
        int j0 = j * n_slices + 1;
        int j1 = (j + 1) * n_slices + 1;
        for (int i = 0; i < n_slices; i++) {
            int i0 = j0 + i;
            int i1 = j0 + (i + 1) % n_slices;
            int i2 = j1 + (i + 1) % n_slices;
            int i3 = j1 + i;
            mesh.add_quad(i0, i1, i3, i2);
        }
    }

    return mesh;
}

#endif