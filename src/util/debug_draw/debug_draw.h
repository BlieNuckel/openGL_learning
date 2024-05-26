#ifndef DEBUG_DRAW_H
#define DEBUG_DRAW_H

#include <Shader.h>
#include <geometry/geometry.h>
#include <glm/glm.hpp>
#include <mesh/mesh.h>

namespace debug_draw {

    class Point {
    private:
        Shader shader;
        Mesh mesh = geometry::uv_sphere(10, 10);
        unsigned int VAO;
        float scale;

    public:
        Point(float scale = 0.02f);

        void draw(glm::vec3 pos, glm::mat4 view, glm::mat4 projection);
    };

} // namespace debug_draw

#endif