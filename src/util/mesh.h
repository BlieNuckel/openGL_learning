#ifndef MESH
#define MESH

using namespace std;
#include <glm/glm.hpp>
#include <math.h>
#include <numbers>
#include <vector>

class Mesh {
private:
    vector<float> _vertices;
    vector<int> _triangles;
    int index = 0;

public:
    Mesh() {}

    int add_vertex(glm::vec3 vertex) {
        _vertices.push_back(vertex.x);
        _vertices.push_back(vertex.y);
        _vertices.push_back(vertex.z);
        return (_vertices.capacity() / 3) - 1;
    }

    void add_triangle(glm::vec3 vertexIndices) {
        _triangles.push_back(vertexIndices.x);
        _triangles.push_back(vertexIndices.y);
        _triangles.push_back(vertexIndices.z);
    }

    void add_quad(glm::vec4 vertexIndices) {
        _triangles.push_back(vertexIndices.x);
        _triangles.push_back(vertexIndices.y);
        _triangles.push_back(vertexIndices.z);
        _triangles.push_back(vertexIndices.w);
        _triangles.push_back(vertexIndices.y);
        _triangles.push_back(vertexIndices.z);
    }

    float *vertices() {
        return _vertices.data();
    }

    int *indices() {
        return _triangles.data();
    }
};

// unsigned int renderMesh(Mesh mesh) {
//     const float *vertices = mesh.vertices();
//     const int *indices = mesh.indices();

//     unsigned int VAO;
//     unsigned int VBO;
//     unsigned int EBO;
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);
//     glGenBuffers(1, &EBO);

//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
//     glEnableVertexAttribArray(0);

//     return VAO;
// }

#endif