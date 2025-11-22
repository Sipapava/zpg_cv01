#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 2) in vec2 aTexCoords;  

out vec2 TexCoords;

uniform mat4 projectMatrix;
uniform mat4 viewMatrix;


void main()
{
    TexCoords = aTexCoords;
    mat4 viewNoTranslation = mat4(mat3(viewMatrix));  
    gl_Position = projectMatrix * viewNoTranslation * vec4(aPos, 1.0);
}
