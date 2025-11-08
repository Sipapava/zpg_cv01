#version 330 core

layout(location = 0) in vec4 vp;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 texCoords; // opraveno

out vec4 fragColor;
out vec2 textCoords;

uniform mat4 modelMatrix;
uniform mat4 projectMatrix;
uniform mat4 viewMatrix;

void main() {
    gl_Position = projectMatrix * viewMatrix * modelMatrix * vp;
    fragColor = normal;
    textCoords = texCoords; // musí odpovídat in
}

