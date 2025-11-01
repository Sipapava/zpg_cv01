#version 330 core

in vec4 fragColor;
in vec4 worldPosition;
in vec3 worldNormal;
out vec4 outColor;

uniform vec3 cameraPos;

#define MAX_LIGHTS 5
struct Light {
    int type;
    vec3 lightPosition;
    vec4 lightColor;
    float specularIntensity;
    float shiness;
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
    
  
    vec4 finalColor = vec4(0.0);

    
    for (int i = 0; i < numberOfLights && i < MAX_LIGHTS; ++i) {
         if(lights[i].type == 3){
          finalColor += lights[i].ambientColor;
         vec3 worldPos3 = vec3(
            worldPosition.x / worldPosition.w,
            worldPosition.y / worldPosition.w,
            worldPosition.z / worldPosition.w);
        vec3 lightToVector = lights[i].lightPosition - worldPos3;
        float distance = length(lightToVector);
        vec3 lightDir = normalize(lightToVector);

        
        float att = 1.0 / (1.0 + (lights[i].attenuation * distance) + (lights[i].attenuation * distance * distance));

       
        float dotProduct = max(dot(lightDir, normalize(worldNormal)), 0.0);
        vec4 diffuse = dotProduct * lights[i].diffuseColor * att;

       
        vec3 viewDir = normalize(cameraPos - worldPosition.xyz);
        vec3 reflectDir = reflect(-lightDir, normalize(worldNormal));
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), lights[i].shiness);
        vec4 specular = lights[i].specularIntensity * spec * lights[i].lightColor * att;

        finalColor += diffuse + specular;
    }}

    outColor = finalColor;
}
