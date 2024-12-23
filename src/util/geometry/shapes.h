#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <mesh/mesh.h>

namespace shapes {
    // SPHERES
    Mesh uv_sphere(int n_slices, int n_stacks);

    // POLYGONS
    Mesh tetrahedron();
    Mesh hexahedron();

    // MESH MODS
    Mesh dual(Mesh &mesh);
}

#endif