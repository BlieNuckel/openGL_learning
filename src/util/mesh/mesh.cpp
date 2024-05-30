#include "mesh.h"
#include <algorithms/algorithms.h>
#include <glm/glm.hpp>
#include <vector>

Mesh::Mesh() {}

Face Mesh::add_face(const std::vector<int> vertices) {
    // Check minimum 3 vertices in face
    const size_t n(vertices.size());
    assert(n > 2);

    // Generate mesh plane
    glm::vec3 p1 = this->vertex(vertices[0]);
    glm::vec3 p2 = this->vertex(vertices[1]);
    glm::vec3 p3 = this->vertex(vertices[2]);
    glm::vec4 plane = algorithms::plane_from_points(p1, p2, p3);

    std::vector<glm::vec3> points;
    points.resize(n);

    for (int i = n - 1; i >= 0; i--) {
        points[i] = this->vertex(vertices[i]);
    }

    // Validate points are on plane
    bool valid = algorithms::all_points_on_plane(plane, points);
    assert(valid);

    // Get offset for new face and insert new vertices
    int face_offset = this->_faces.size();
    this->_vertices.insert(this->_vertices.end(), vertices.begin(), vertices.end());

    // Create new face and save to faces vector
    Face new_face(face_offset, n);
    this->_faces.push_back(new_face);

    return new_face;
}

int Mesh::add_vertex(glm::vec3 vertex) {
    _vertices.push_back(vertex);
    return (_vertices.size());
}

Face Mesh::add_triangle(int i0, int i1, int i2) {
    this->add_indices_.resize(3);

    add_indices_[0] = i0;
    add_indices_[1] = i1;
    add_indices_[2] = i2;

    return this->add_face(add_indices_);
}

Face Mesh::add_quad(int i0, int i1, int i2, int i3) {
    this->add_indices_.resize(4);

    add_indices_[0] = i0;
    add_indices_[1] = i1;
    add_indices_[2] = i2;
    add_indices_[3] = i3;

    return this->add_face(add_indices_);
}

glm::vec3 *Mesh::vertices() {
    return _vertices.data();
}

int *Mesh::indices() {
    return _triangles.data();
}

glm::vec3 Mesh::vertex(int index) {
    return _vertices[index];
}