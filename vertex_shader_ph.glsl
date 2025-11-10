#version 330 core

layout(location = 0) in vec4 vp;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 texCoords; 

out vec4 fragColor;
out vec4 worldPosition;
out vec3 worldNormal;
out vec2 textCoords;

uniform mat4 modelMatrix;
uniform mat4 projectMatrix;
uniform mat4 viewMatrix;

void main()
{
    gl_Position = projectMatrix * viewMatrix * modelMatrix * vp;
    fragColor = normal;
    worldPosition = modelMatrix * vp;
    vec3 n = vec3(normal.x / normal.w,
              normal.y / normal.w,
              normal.z / normal.w);
    worldNormal = normalize(transpose(inverse(mat3(modelMatrix))) * n);
      textCoords = texCoords;
}
