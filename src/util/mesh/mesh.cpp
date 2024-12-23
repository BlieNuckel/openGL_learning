#define GLM_ENABLE_EXPERIMENTAL
#include "mesh.h"
#include <algorithm>
#include <algorithms/algorithms.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

Mesh::Mesh() {}

Face Mesh::add_face(const std::vector<int> &vertex_i) {
    // Check minimum 3 vertices in face
    const size_t n(vertex_i.size());
    if (n <= 2) {
        throw std::invalid_argument("At least 3 vertices are required to create a face.");
    }

    // Generate mesh plane
    auto p1 = this->vertex(vertex_i[0]);
    auto p2 = this->vertex(vertex_i[1]);
    auto p3 = this->vertex(vertex_i[2]);
    auto plane = algorithms::plane_from_points(p1, p2, p3);

    std::cout << "Plane: " + glm::to_string(plane) << std::endl;

    std::vector<glm::vec3> points;
    points.resize(n);

    for (int i = n - 1; i >= 0; i--) {
        points[i] = this->vertex(vertex_i[i]);
    }

    // Validate points are on plane
    bool valid = algorithms::all_points_on_plane(plane, points);
    if (!valid) {
        std::cout << "add_face::points_not_on_plane" + glm::to_string(plane) << std::endl;
        throw std::runtime_error("Invalid plane generation attempted");
    }

    glm::vec3 plane_normal = glm::normalize(glm::cross(p1 - p2, p3 - p2));
    glm::vec3 plane_origin = algorithms::centroid(points);

    std::vector<float> angles;
    std::transform(points.begin(), points.end(), std::back_inserter(angles), [&](glm::vec3 point) {
        glm::vec3 point_norm = plane_origin - point;
        return glm::orientedAngle(glm::vec3(0.0f, 0.0f, 0.0f), point_norm, plane_normal);
    });

    for (auto &&angle : angles) {
        std::cout << angle << ' ';
    }

    // Get offset for new face and insert new vertices
    int face_offset = this->_faces.size();
    this->_vertices.insert(this->_vertices.end(), vertex_i.begin(), vertex_i.end());

    // Create new face and save to faces vector
    Face new_face(face_offset, n);
    this->_faces.push_back(new_face);

    return new_face;
}

int Mesh::add_vertex(glm::vec3 vertex) {
    _vertices.push_back(vertex.x);
    _vertices.push_back(vertex.y);
    _vertices.push_back(vertex.z);
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

float *Mesh::vertices() {
    return _vertices.data();
}

int *Mesh::indices() {
    return _triangles.data();
}

glm::vec3 Mesh::vertex(int index) {
    return glm::vec3(_vertices[index], _vertices[index + 1], _vertices[index + 2]);
}