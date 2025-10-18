#version 330 core

in vec4 fragColor;
in vec4 worldPosition;
in vec3 worldNormal;
out vec4 outColor;

uniform vec3 cameraPos;
uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform float specularIntensity;
uniform float shiness;

void main()
{
   
    vec3 lightToVector = lightPosition - worldPosition.xyz;

    float dotProduct = max(dot(normalize(lightToVector), normalize(worldNormal)), 0.0);
    vec4 diffuse = dotProduct * vec4(0.385, 0.647, 0.812, 1.0); //tady barvu
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0); //tady barvu

    vec3 viewDir = normalize(cameraPos - worldPosition.xyz);
    vec3 halfwayDir = normalize(normalize(lightToVector) + normalize(viewDir));
    float spec = pow(max(dot(worldNormal, halfwayDir), 0.0), shiness); //shinnes
    vec4 specular = specularIntensity * spec * lightColor; //jeste intezita by tu mohla byt

    outColor = ambient + diffuse + specular;
}
