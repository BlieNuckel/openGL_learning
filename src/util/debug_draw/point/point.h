// #ifndef DEBUG_DRAW_POINT
// #define DEBUG_DRAW_POINT

// #include <Shader.h>
// #include <glad/glad.h>
// #include <textures/texture_loader.h>

// #include "../1.10_sphere/uv_sphere.h"
// #include <GLFW/glfw3.h>
// #include <glm/glm.hpp>
// #include <math.h>
// #include <mesh/draw_mesh.h>
// #include <mesh/mesh.h>
// #include <numbers>
// #include <vector>

// class Point {
// private:
//     Shader shader;
//     Mesh mesh = uv_sphere(10, 10);
//     unsigned int VAO;
//     float scale;

// public:
//     Point(float scale = 0.02f) : shader("../util/debug_draw/point/shaders/point_shader.vs", "../util/debug_draw/point/shaders/point_shader.fs") {
//         this->scale = scale;
//         this->VAO = renderMesh(this->mesh);
//     }

//     void draw(glm::vec3 pos, glm::mat4 view, glm::mat4 projection) {
//         glBindVertexArray(this->VAO);

//         glm::mat4 model = glm::mat4(1.0f);
//         model = glm::translate(model, pos);
//         model = glm::scale(model, glm::vec3(this->scale));

//         shader.use();
//         shader.setMat4fv("model", model);
//         shader.setMat4fv("view", view);
//         shader.setMat4fv("projection", projection);

//         glDrawElements(GL_TRIANGLES, this->mesh._triangles.size(), GL_UNSIGNED_INT, 0);

//         glBindVertexArray(0);
//     }
// };

// #endif