#version 330 core

in vec4 fragColor;
in vec2 textCoords;
out vec4 outColor;

uniform vec4 color;
uniform sampler2D texture_test; // jméno uniformu musí odpovídat názvu v texture()

void main() {
    // vzorek z textury
    vec4 texColor = texture(texture_test, textCoords); // použijeme správný uniform

    // pokud textura existuje (neprùhledná), použij ji, jinak fallback barvu
    if(texColor.a > 0.0)
        outColor = texColor;
    else
        outColor = color;
}

