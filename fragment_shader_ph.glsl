#version 330 core

in vec4 fragColor;
in vec4 worldPosition;
in vec3 worldNormal;
out vec4 outColor;

uniform vec3 cameraPos;

void main()
{
    vec3 lightPosition = vec3(0.0, 0.0, 0.0); // Point Light position
    vec3 lightToVector = lightPosition - worldPosition.xyz;

    float dotProduct = max(dot(normalize(lightToVector), normalize(worldNormal)), 0.0);
    vec4 diffuse = dotProduct * vec4(0.385, 0.647, 0.812, 1.0);
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

    vec3 viewDir = normalize(cameraPos - worldPosition.xyz);
    vec3 reflectDir = reflect(-normalize(lightToVector), normalize(worldNormal));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec4 specular = spec * vec4(1.0, 1.0, 1.0, 1.0); //jeste intezita by tu mohla byt

    outColor = ambient + diffuse + specular;
}
