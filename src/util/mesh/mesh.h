#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <math.h>
#include <numbers>
#include <vector>

class Mesh {
public:
    std::vector<int> add_indices_;

    std::vector<glm::vec3> _vertices;
    std::vector<Face> _faces;
    std::vector<int> _triangles;

    Mesh();

    int add_vertex(glm::vec3 vertex);

    glm::vec3 vertex(int index);

    Face add_triangle(int index1, int index2, int index3);

    Face add_quad(int index1, int index2, int index3, int index4);

    glm::vec3 *vertices();

    int *indices();

private:
    Face add_face(const std::vector<int>);
};

class Face {
public:
    Face(int offset, int size) {
        this->offset = offset;
        this->size = size;
    };

    int offset;
    int size;
};

#endif