#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D pointTexture;

void main() {
    FragColor = texture2D(pointTexture, TexCoord);
}