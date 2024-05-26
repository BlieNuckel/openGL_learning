
#include "../debug_draw.h"
#include <Shader.h>
#include <glad/glad.h>
#include <textures/texture_loader.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <math.h>
#include <mesh/draw_mesh.h>
#include <mesh/mesh.h>
#include <numbers>
#include <vector>

debug_draw::Point::Point(float scale) : shader("../util/debug_draw/point/shaders/point_shader.vs", "../util/debug_draw/point/shaders/point_shader.fs") {
    this->scale = scale;
    this->VAO = renderMesh(this->mesh);
};

void debug_draw::Point::draw(glm::vec3 pos, glm::mat4 view, glm::mat4 projection) {
    glBindVertexArray(this->VAO);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::scale(model, glm::vec3(this->scale));

    shader.use();
    shader.setMat4fv("model", model);
    shader.setMat4fv("view", view);
    shader.setMat4fv("projection", projection);

    glDrawElements(GL_TRIANGLES, this->mesh._triangles.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
};
