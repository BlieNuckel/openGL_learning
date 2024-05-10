#ifndef GEOMETRY_HELPERS_H
#define GEOMETRY_HELPERS_H

#include <mesh/mesh.h>

Mesh dual_poly(Mesh &mesh);
Mesh centroid(const Mesh &mesh, Face f);

#endif