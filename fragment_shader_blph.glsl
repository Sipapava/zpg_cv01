#version 330 core

in vec4 fragColor;
in vec4 worldPosition;
in vec3 worldNormal;
out vec4 outColor;

uniform vec3 cameraPos;

#define MAX_LIGHTS 5
struct Light {
    vec3 lightPosition;
    vec4 lightColor;
    float specularIntensity;
    float shiness;
    float attenuation;
    vec4 diffuseColor;
};
uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;

void main()
{
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    vec4 finalColor = ambient;

    for (int i = 0; i < numberOfLights && i < MAX_LIGHTS; ++i) {
        vec3 worldPos3 = vec3(
            worldPosition.x / worldPosition.w,
            worldPosition.y / worldPosition.w,
            worldPosition.z / worldPosition.w);
        vec3 lightToVector = lights[i].lightPosition - worldPos3;
        float distance = length(lightToVector);
        float attenuation  = 1.0 / (1.0 + (lights[i].attenuation * distance) + (lights[i].attenuation * distance * distance));


        float dotProduct = smoothstep(0.0, 1.0, dot(normalize(lightToVector), normalize(worldNormal)));
        vec4 diffuse = dotProduct * lights[i].diffuseColor;

        float spec = 0.0;
        if (dotProduct > 0.0) { //chyba pokud toto neni
            vec3 viewDir = normalize(cameraPos - worldPosition.xyz);
            vec3 halfwayDir = normalize(normalize(lightToVector) + normalize(viewDir));
            spec = pow(max(dot(worldNormal, halfwayDir), 0.0), lights[i].shiness);
        }

        vec4 specular = lights[i].specularIntensity * spec * lights[i].lightColor;
        specular *= dotProduct; //chyba pokud toto neni
        //zrcadlova slozka pri nizke shinnes prosvita, protoze se pocita i kdyz neni videt difusni slozka
        diffuse *= attenuation;
        specular *= attenuation;

        finalColor += diffuse + specular;
    }

    outColor = finalColor;
}
