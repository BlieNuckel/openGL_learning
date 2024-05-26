#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <math.h>
#include <numbers>
#include <vector>

class Mesh {
public:
    std::vector<float> _vertices;
    std::vector<int> _triangles;

    Mesh();

    int add_vertex(glm::vec3 vertex);

    void add_triangle(int index1, int index2, int index3);

    void add_quad(int index1, int index2, int index3, int index4);

    float *vertices();

    int *indices();
};

#endif