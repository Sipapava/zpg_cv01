#version 330 core

in vec4 fragColor;
in vec4 worldPosition;
in vec3 worldNormal;
out vec4 outColor;

void main()
{
    vec3 lightPosition= vec3(0.0,0.0,0.0); //Point Light position
    vec3 lightToVector = lightPosition - worldPosition.xyz;
    float dotProduct = max(dot(normalize(lightToVector), normalize(worldNormal)), 0.0);
    vec4 diffuse = dotProduct * vec4( 0.385, 0.647, 0.812, 1.0);
    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
    outColor = ambient + diffuse;
}
