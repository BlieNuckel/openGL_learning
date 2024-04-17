#include "../util/GlfwInit.h"
#include "../util/Shader.h"
#include "../util/stb_image.h"
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>
#include <math.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void renderInit();
unsigned int loadTexture(const char *texturePath, const GLenum format, const GLint sWrap, const GLint tWrap);

unsigned int VAO;
float vertices[] = {
    // positions      // colors         // texture coords
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
};
unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};
float mixPercentage = 0.0f;

int main(int argc, char const *argv[]) {
    GLFWwindow *window = initGlfw(framebuffer_size_callback);
    if (window == NULL) {
        return -1;
    }

    renderInit();
    unsigned int texture1 = loadTexture("D:/Coding/openGL/src/1.6/resources/container.jpg", GL_RGB, GL_REPEAT, GL_REPEAT);
    unsigned int texture2 = loadTexture("D:/Coding/openGL/src/1.6/resources/awesomeface.png", GL_RGBA, GL_REPEAT, GL_REPEAT);

    if (texture1 == -1 || texture2 == -1) {
        return -1;
    }

    Shader shader("D:/Coding/openGL/src/1.6/shaders/shader.vs", "D:/Coding/openGL/src/1.6/shaders/shader.fs");

    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        shader.setFloat("mixPercentage", mixPercentage);

        // render stuff
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void renderInit() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    unsigned int VBO;
    unsigned int EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

unsigned int loadTexture(const char *texturePath, const GLenum format, const GLint sWrap, const GLint tWrap) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_NEAREST, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_NEAREST, GL_NEAREST);

    int width;
    int height;
    int nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
        return -1;
    }

    stbi_image_free(data);
    return texture;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        mixPercentage = std::max(mixPercentage - 0.001f, 0.0f);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        mixPercentage = std::min(mixPercentage + 0.001f, 1.0f);
    }
}