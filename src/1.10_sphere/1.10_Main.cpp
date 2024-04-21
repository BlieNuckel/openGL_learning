#include "../util/GlfwInit.h"
#include "../util/Shader.h"
#include "../util/fly_camera.h"
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <algorithm>
#include <glm/glm.hpp>
#include <iostream>
#include <math.h>
#include <mesh.h>
#include <point.h>
#include <uv_sphere.h>

const char vertexShader[] = "../../src/1.10_sphere/shaders/shader.vs";
const char fragShader[] = "../../src/1.10_sphere/shaders/shader.fs";

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void renderInit();
void calcTiming();
void clearBuffers();

// MARK: GLOBALS
// screen
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
FlyCam camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool cameraMouseControl = false;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

Mesh uv_sphere_mesh = uv_sphere(10, 10);
unsigned int VAO;

int main() {
    GLFWwindow *window = initGlfw(SCR_WIDTH, SCR_HEIGHT, framebuffer_size_callback);
    if (window == NULL) {
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    renderInit();

    Shader shader(vertexShader, fragShader);

    while (!glfwWindowShouldClose(window)) {
        calcTiming();
        processInput(window);
        clearBuffers();
        shader.use();

        // glDrawElements(GL_TRIANGLES, sizeof(uv_sphere_mesh.indices()), GL_UNSIGNED_INT, 0);

        drawPoint(glm::vec3(0.0f, 0.0f, 0.0f));
        drawPoint(glm::vec3(0.0f, 5.0f, 0.0f));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void renderInit() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    VAO = renderMesh(uv_sphere_mesh);
}

void calcTiming() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void clearBuffers() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

// MARK: CONTROLS
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        if (!cameraMouseControl) {
            firstMouse = true;
        }
        cameraMouseControl = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        cameraMouseControl = false;
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (!cameraMouseControl) {
        return;
    }

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = ypos - lastY;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}