#ifndef DEBUG_DRAW_POINT
#define DEBUG_DRAW_POINT
using namespace std;

#include <Shader.h>
#include <glad/glad.h>
#include <textures/texture_loader.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <math.h>
#include <numbers>
#include <vector>

class Point {
private:
    Shader shader;
    unsigned int VAO;
    float scale;
    glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);
    unsigned int pointTexture = loadTexture("../util/debug_draw/point/resources/point.png", GL_RGBA, GL_REPEAT, GL_REPEAT);
    float vertices[20] = {
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f
    };
    unsigned int indices[6] = {
        0, 1, 2,
        0, 2, 3
    };

public:
    Point(float scale = 1.0f) : shader("../util/debug_draw/point/shaders/point_shader.vs", "../util/debug_draw/point/shaders/point_shader.fs") {
        this->scale = scale;

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        unsigned int EBO, VBO;

        glGenBuffers(1, &EBO);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        shader.use();
        shader.setInt("pointTexture", 0);

        glBindVertexArray(0);
    }

    void draw(glm::vec3 pos, glm::vec3 cameraDirection, glm::mat4 view, glm::mat4 projection) {
        shader.use();
        glBindVertexArray(VAO);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, pointTexture);
        glBindVertexArray(VAO);

        glm::vec3 rot = glm::cross(glm::normalize(cameraDirection), -1.0f * glm::normalize(cameraDirection));
        float angle = glm::dot(cameraDirection, direction);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        model = glm::scale(model, glm::vec3(scale));
        // model = glm::rotate(model, angle, rot);
        shader.setMat4fv("model", model);
        shader.setMat4fv("view", view);
        shader.setMat4fv("projection", projection);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        direction = -1.0f * cameraDirection;
    }
};

#endif