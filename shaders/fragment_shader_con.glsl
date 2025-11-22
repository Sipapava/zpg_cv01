#version 330 core

in vec4 fragColor; //zbytecne asi
in vec2 textCoords;
out vec4 outColor;

uniform vec4 color;
uniform sampler2D texture_test;

void main() {

    vec4 texColor = texture(texture_test, textCoords); 


    if(texColor.a > 0.0)
        outColor = texColor;
    else
        outColor = color;
}

