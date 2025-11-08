#version 330 core
layout(location = 0) in vec4 aPos;

out vec3 TexCoords;

uniform mat4 projectMatrix;
uniform mat4 viewMatrix;

void main()
{
    TexCoords = aPos.xyz;

    mat4 viewNoTranslation = mat4(mat3(viewMatrix));
     gl_Position = projectMatrix * viewNoTranslation * aPos;
}
