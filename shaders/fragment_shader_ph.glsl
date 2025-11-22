#version 330 core

in vec4 fragColor;
in vec4 worldPosition;
in vec3 worldNormal;
out vec4 outColor;
in vec2 textCoords;

uniform vec3 cameraPos;

#define MAX_LIGHTS 5
struct Light {
    int type;
    vec3 lightPosition;
   
    float specularIntensity;
          
    float attenuation;
    
    
    vec3 direction;
    float angleReflector;
};

struct Material{
    vec4 diffuseColor;
    vec4 ambientColor;
    vec4 lightColor;
    float shiness;
};


uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;
uniform sampler2D texture_test;
uniform vec4 color;
uniform Material material;

void main()
{
    vec4 finalColor = vec4(0.0);

    for (int i = 0; i < numberOfLights && i < MAX_LIGHTS; ++i) {

        if (lights[i].type == 1) {
            finalColor += material.ambientColor;
        }

     
        if (lights[i].type == 2) {
            vec3 lightDir = normalize(-lights[i].direction); 
            vec3 norm = normalize(worldNormal);

            // nepoužívat smoothstep zde, prostì max(0,dot)
            float dotProduct = max(dot(norm, lightDir), 0.0);
            vec4 diffuse = dotProduct * material.diffuseColor;

            float spec = 0.0;
            if (dotProduct > 0.0) {
                 vec3 worldPos3 = vec3(
                        worldPosition.x / worldPosition.w,
                        worldPosition.y / worldPosition.w,
                        worldPosition.z / worldPosition.w);
                vec3 viewDir = normalize(cameraPos - worldPos3);
                vec3 reflectDir = reflect(-lightDir, norm); 
                spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shiness);
            }

            vec4 specular = lights[i].specularIntensity * spec * material.lightColor;
            specular *= dotProduct;
            finalColor += diffuse + specular;
        }

   
        if(lights[i].type == 3) {
            vec3 norm = normalize(worldNormal);
            vec3 worldPos3 = vec3(
                        worldPosition.x / worldPosition.w,
                        worldPosition.y / worldPosition.w,
                        worldPosition.z / worldPosition.w);
            vec3 lightToVector = lights[i].lightPosition - worldPos3;
            float distance = length(lightToVector);
            vec3 lightDir = normalize(lightToVector);

       
            float att = 1.0 / (1.0 + lights[i].attenuation * distance + lights[i].attenuation * distance * distance);

            float dotProduct = max(dot(norm, lightDir), 0.0);
            vec4 diffuse = dotProduct * material.diffuseColor * att;

            float spec = 0.0;
            if (dotProduct > 0.0) {
                vec3 viewDir = normalize(cameraPos - worldPos3);
                vec3 reflectDir = reflect(-lightDir, norm);
                spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shiness);
            }

            vec4 specular = lights[i].specularIntensity * spec * material.lightColor * att;
            specular *= dotProduct;
            finalColor += diffuse + specular;
        }

        if (lights[i].type == 4) {
                vec3 worldPos3 = vec3(
                    worldPosition.x / worldPosition.w,
                    worldPosition.y / worldPosition.w,
                    worldPosition.z / worldPosition.w);
            vec3 lightDir = normalize(lights[i].lightPosition - worldPos3); 
            vec3 spotDir = normalize(-lights[i].direction);               

            float theta = dot(lightDir, spotDir);                          
            float epsilon = cos(lights[i].angleReflector);               

            if (theta > epsilon) { 
                float distance = length(lights[i].lightPosition - worldPos3);
                float attenuation = 1.0 / (1.0 + lights[i].attenuation * distance + lights[i].attenuation * distance * distance);

                vec3 norm = normalize(worldNormal);
                float dotProduct = max(dot(norm, lightDir), 0.0);
                vec4 diffuse = dotProduct * material.diffuseColor * attenuation;

                float spec = 0.0;
                if(dotProduct > 0.0){
                    vec3 viewDir = normalize(cameraPos - worldPos3);
                    vec3 reflectDir = reflect(-lightDir, norm);  
                    spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shiness);
                }
                vec4 specular = lights[i].specularIntensity * spec * material.lightColor * attenuation;
                specular *= dotProduct;
                finalColor += diffuse + specular;
            }
        }


    }
    vec4 texColor = texture(texture_test, textCoords);
    
    if(texColor.a > 0.0)
        outColor = texColor * finalColor;
    else
        outColor = color * finalColor;

   
}
