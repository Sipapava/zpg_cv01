#version 330

in vec4 fragColor;
out vec4 outColor;


uniform vec4 color;

void main() {
    outColor = color;
}
