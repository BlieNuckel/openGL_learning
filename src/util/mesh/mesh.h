#ifndef MESH_H
#define MESH_H

using namespace std;
#include <glm/glm.hpp>
#include <math.h>
#include <numbers>
#include <vector>

class Mesh {
public:
    vector<float> _vertices;
    vector<int> _triangles;

    Mesh() {}

    int add_vertex(glm::vec3 vertex) {
        _vertices.push_back(vertex.x);
        _vertices.push_back(vertex.y);
        _vertices.push_back(vertex.z);
        return (_vertices.size() / 3) - 1;
    }

    void add_triangle(int index1, int index2, int index3) {
        _triangles.push_back(index1);
        _triangles.push_back(index2);
        _triangles.push_back(index3);
    }

    void add_quad(int index1, int index2, int index3, int index4) {
        _triangles.push_back(index1);
        _triangles.push_back(index2);
        _triangles.push_back(index3);
        _triangles.push_back(index1);
        _triangles.push_back(index3);
        _triangles.push_back(index4);
    }

    float *vertices() {
        return _vertices.data();
    }

    int *indices() {
        return _triangles.data();
    }
};

#endif