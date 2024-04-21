using namespace std;
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <math.h>
#include <numbers>
#include <texture_loader.h>
#include <vector>

const float vertices[] = {
    -1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, -1.0, 0.0,
    -1.0, -1.0, 0.0
};
const unsigned int indices[] = {
    0, 1, 2,
    1, 2, 3
};

void drawPoint(glm::vec3 pos) {
    unsigned int VAO;
    unsigned int EBO;
    unsigned int VBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, 1, GL_FALSE, indices);
}