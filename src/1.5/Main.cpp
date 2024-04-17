#include "../util/GlfwInit.h"
#include "../util/Shader.h"
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void renderInit();

unsigned int VBO;
unsigned int VAO;

float vertices[] = {
    // positions        // colors
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // top
};
unsigned int indices[] = {
    0, 1, 2
};

int main() {
    GLFWwindow* window = initGlfw(framebuffer_size_callback);
    if (window == NULL) {
        return -1;
    }

    Shader ourShader("D:/Coding/openGL/src/1.5/shaders/shader.vs", "D:/Coding/openGL/src/1.5/shaders/shader.fs");

    renderInit();

    while (!glfwWindowShouldClose(window)) {
        // input
        processInput(window);

        // clear colorBuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // use shader
        ourShader.use();
        ourShader.setFloat("horizontalOffset", 0.5f);

        // rendering commands
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void renderInit() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}