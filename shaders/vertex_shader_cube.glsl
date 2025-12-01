#version 330 core
layout(location = 0) in vec4 aPos;

out vec3 TexCoords;

uniform mat4 projectMatrix;
uniform mat4 viewMatrix;

void main()
{
    TexCoords = vec3(aPos.x / aPos.w,
              aPos.y / aPos.w,
              aPos.z / aPos.w);

    mat4 viewNoTranslation = mat4(mat3(viewMatrix));
     gl_Position = projectMatrix * viewNoTranslation * aPos;
}
