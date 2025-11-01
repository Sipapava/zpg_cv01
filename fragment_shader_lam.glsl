#version 330 core

in vec4 fragColor;
in vec4 worldPosition;
in vec3 worldNormal;
out vec4 outColor;

#define MAX_LIGHTS 5
struct Light {
    int type;
    vec3 lightPosition;
    float attenuation;
    vec4 diffuseColor;
    vec4 ambientColor;
    vec3 direction;
    float angleReflector;
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;

void main()
{
     vec4 ambientFinal = vec4(0.0);
    vec4 diffuse = vec4(0.0);

    for (int i = 0; i < numberOfLights && i < MAX_LIGHTS; ++i) {
     if(lights[i].type == 3){
         ambientFinal += lights[i].ambientColor;
         vec3 worldPos3 = vec3(
            worldPosition.x / worldPosition.w,
            worldPosition.y / worldPosition.w,
            worldPosition.z / worldPosition.w);
        vec3 lightToVector = lights[i].lightPosition - worldPos3;
        float distance = length(lightToVector);
     
        float dotProduct = max(dot(normalize(lightToVector), normalize(worldNormal)), 0.0);

        
        float att = 1.0 / (1.0 + lights[i].attenuation * distance * distance);

        diffuse += dotProduct * lights[i].diffuseColor * att;
    }

    outColor = diffuse + ambientFinal;
    }
}
