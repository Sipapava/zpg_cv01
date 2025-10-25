

#version 330 core

in vec4 fragColor;
in vec4 worldPosition;
in vec3 worldNormal;
out vec4 outColor;

uniform vec3 cameraPos;

#define MAX_LIGHTS 5
struct Light{
 vec3 lightPosition;
 vec4 lightColor;
 float specularIntensity;
 float shiness;
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;

void main()
{
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    vec4 finalColor = ambient;

    // projdeme všechna svìtla
    for (int i = 0; i < numberOfLights && i < MAX_LIGHTS; ++i) {
        vec3 lightToVector = lights[i].lightPosition - worldPosition.xyz;

        float dotProduct = smoothstep(0.0, 1.0, dot(normalize(lightToVector), normalize(worldNormal)));
        vec4 diffuse = dotProduct * vec4(0.385, 0.647, 0.812, 1.0);

        float spec = 0.0;
        if (dotProduct > 0.0) {
            vec3 viewDir = normalize(cameraPos - worldPosition.xyz);
            vec3 halfwayDir = normalize(normalize(lightToVector) + normalize(viewDir));
            spec = pow(max(dot(worldNormal, halfwayDir), 0.0), lights[i].shiness);
        }
        vec4 specular = lights[i].specularIntensity * spec * lights[i].lightColor;
        specular *= dotProduct; // pro zjemnìní ostrých hran

        finalColor += diffuse + specular;
    }

    outColor = finalColor;
}

