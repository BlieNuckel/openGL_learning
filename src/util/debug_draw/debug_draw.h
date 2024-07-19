#ifndef DEBUG_DRAW_H
#define DEBUG_DRAW_H

#include <Shader.h>
#include <glm/glm.hpp>
#include <mesh/mesh.h>
#include <shapes/shapes.h>

namespace debug_draw {

    class Point {
    private:
        Shader shader;
        Mesh mesh = shapes::uv_sphere(10, 10);
        unsigned int VAO;
        float scale;

    public:
        Point(float scale = 0.02f);

        void draw(glm::vec3 pos, glm::mat4 view, glm::mat4 projection);
    };

} // namespace debug_draw

#endif