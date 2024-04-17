#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec4 vertexColor;
uniform float horizontalOffset;

void main() {
    vec4 pos = vec4(aPos.x + horizontalOffset, aPos.y, aPos.z, 1.0);
    gl_Position = pos;
    vertexColor = pos;
}