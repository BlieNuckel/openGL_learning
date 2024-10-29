#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <mesh/mesh.h>

namespace geometry {
    Mesh uv_sphere(int n_slices, int n_stacks);
    Mesh tetrahedron();
    Mesh hexahedron();
    Mesh dual(Mesh &mesh);
}

#endif