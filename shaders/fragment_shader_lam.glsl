#version 330 core


in vec4 worldPosition;
in vec3 worldNormal;
out vec4 outColor;
in vec2 textCoords;

#define MAX_LIGHTS 5
struct Light {
    int type;               
    vec3 lightPosition;
    float attenuation;
   
    vec3 direction;
    float angleReflector;
};

struct Material{
    vec4 diffuseColor;
    vec4 ambientColor;
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;
uniform sampler2D texture_test;
uniform vec4 color;
uniform Material material;

void main()
{
    vec4 ambientFinal = vec4(0.0);
    vec4 diffuseFinal = vec4(0.0);
    vec3 norm = normalize(worldNormal);
    vec3 worldPos3 = vec3(
                        worldPosition.x / worldPosition.w,
                        worldPosition.y / worldPosition.w,
                        worldPosition.z / worldPosition.w);

    for (int i = 0; i < numberOfLights && i < MAX_LIGHTS; ++i) {
        if (lights[i].type == 1) { 
            ambientFinal += material.ambientColor;
        } 
        else if (lights[i].type == 2) { 
            vec3 lightDir = normalize(-lights[i].direction);
            float dotProduct = max(dot(norm, lightDir), 0.0);
            vec4 diffuse = dotProduct * material.diffuseColor;
            diffuseFinal += diffuse;
        } 
        else if (lights[i].type == 3) {
            vec3 lightToVector = lights[i].lightPosition - worldPos3;
            float distance = length(lightToVector);
            float att =  1.0 / (1.0 + lights[i].attenuation * distance + lights[i].attenuation * distance * distance);
            vec3 lightDir = normalize(lightToVector);
            float dotProduct = max(dot(norm, lightDir), 0.0);
            vec4 diffuse = dotProduct * material.diffuseColor * att;
            diffuseFinal += diffuse;
        } 
        else if (lights[i].type == 4) { 
            vec3 lightToVector = lights[i].lightPosition - worldPos3;
            vec3 lightDir = normalize(lightToVector);
            vec3 spotDir = normalize(-lights[i].direction);
            float theta = dot(lightDir, spotDir);
            float epsilon = cos(lights[i].angleReflector);

            if (theta > epsilon) {
                float distance = length(lightToVector);
                float att =  1.0 / (1.0 + lights[i].attenuation * distance + lights[i].attenuation * distance * distance);
                float dotProduct = max(dot(norm, lightDir), 0.0);
                vec4 diffuse = dotProduct * material.diffuseColor * att;
                
                diffuseFinal += diffuse;
            }
        }
    }

    vec4 texColor = texture(texture_test, textCoords); 
    if(texColor.a > 0.0)
        outColor = texColor * (diffuseFinal + ambientFinal);
    else
        outColor = color*(diffuseFinal + ambientFinal);
}
