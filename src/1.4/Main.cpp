#include "../util/GlfwInit.h"
#include "../util/Shader.h"
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void renderInit();

unsigned int VBOs[2];
unsigned int VAOs[2];
float leftTriangle[] = {
    -1.0f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    0.0f, -0.5f, 0.0f
};
float rightTriangle[] = {
    0.0f, -0.5f, 0.0f,
    1.0f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f
};

int main() {
    GLFWwindow* window = initGlfw(framebuffer_size_callback);
    if (window == NULL) {
        return -1;
    }

    Shader leftShader("D:/Coding/openGL/src/1.4/shaders/shader.vs", "D:/Coding/openGL/src/1.4/shaders/leftShader.fs");
    Shader rightShader("D:/Coding/openGL/src/1.4/shaders/shader.vs", "D:/Coding/openGL/src/1.4/shaders/rightShader.fs");

    renderInit();

    while (!glfwWindowShouldClose(window)) {
        // input
        processInput(window);

        // clear colorBuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw left triangle
        leftShader.use();
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // draw right triangle
        rightShader.use();
        glBindVertexArray(VAOs[1]);
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

    glGenBuffers(2, VBOs);
    glGenVertexArrays(2, VAOs);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(leftTriangle), leftTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rightTriangle), rightTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}
