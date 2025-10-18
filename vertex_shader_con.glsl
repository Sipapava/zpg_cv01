#version 330

layout(location = 0) in vec4 vp;
layout(location = 1) in vec4 color;

out vec4 fragColor;

uniform mat4 modelMatrix;
uniform mat4 projectMatrix;
uniform mat4 viewMatrix;

void main() {
    gl_Position = projectMatrix * viewMatrix * modelMatrix * vp;
    fragColor = color;
}
