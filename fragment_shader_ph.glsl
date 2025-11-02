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

        // Ambientní svìtlo
        if (lights[i].type == 1) {
            finalColor += lights[i].ambientColor;
        }

        // Directional light
        if (lights[i].type == 2) {
            vec3 lightDir = normalize(-lights[i].direction); 
            vec3 norm = normalize(worldNormal);

            // nepoužívat smoothstep zde, prostì max(0,dot)
            float dotProduct = max(dot(norm, lightDir), 0.0);
            vec4 diffuse = dotProduct * lights[i].diffuseColor;

            float spec = 0.0;
            if (dotProduct > 0.0) {
                 vec3 worldPos3 = vec3(
                        worldPosition.x / worldPosition.w,
                        worldPosition.y / worldPosition.w,
                        worldPosition.z / worldPosition.w);
                vec3 viewDir = normalize(cameraPos - worldPos3);
                vec3 reflectDir = reflect(-lightDir, norm); // reflektujeme smìrem *k svìtlu*
                spec = pow(max(dot(viewDir, reflectDir), 0.0), lights[i].shiness);
            }

            vec4 specular = lights[i].specularIntensity * spec * lights[i].lightColor;
            specular *= dotProduct;
            finalColor += diffuse + specular;
        }

        // Point / spot light
        if(lights[i].type == 3) {
            vec3 norm = normalize(worldNormal);
            vec3 worldPos3 = vec3(
                        worldPosition.x / worldPosition.w,
                        worldPosition.y / worldPosition.w,
                        worldPosition.z / worldPosition.w);
            vec3 lightToVector = lights[i].lightPosition - worldPos3;
            float distance = length(lightToVector);
            vec3 lightDir = normalize(lightToVector);

            // opravená attenuation
            float att = 1.0 / (1.0 + lights[i].attenuation * distance + lights[i].attenuation * distance * distance);

            float dotProduct = max(dot(norm, lightDir), 0.0);
            vec4 diffuse = dotProduct * lights[i].diffuseColor * att;

            float spec = 0.0;
            if (dotProduct > 0.0) {
                vec3 viewDir = normalize(cameraPos - worldPos3);
                vec3 reflectDir = reflect(-lightDir, norm);
                spec = pow(max(dot(viewDir, reflectDir), 0.0), lights[i].shiness);
            }

            vec4 specular = lights[i].specularIntensity * spec * lights[i].lightColor * att;
            specular *= dotProduct;
            finalColor += diffuse + specular;
        }

        if (lights[i].type == 4) { // spotlight
                vec3 worldPos3 = vec3(
                    worldPosition.x / worldPosition.w,
                    worldPosition.y / worldPosition.w,
                    worldPosition.z / worldPosition.w);
            vec3 lightDir = normalize(lights[i].lightPosition - worldPos3); 
            vec3 spotDir = normalize(-lights[i].direction);               

            float theta = dot(lightDir, spotDir);                          
            float epsilon = cos(lights[i].angleReflector);               

            if (theta > epsilon) {  // v kuželu reflektoru
                float distance = length(lights[i].lightPosition - worldPos3);
                float attenuation = 1.0 / (1.0 + lights[i].attenuation * distance + lights[i].attenuation * distance * distance);

                vec3 norm = normalize(worldNormal);
                float dotProduct = max(dot(norm, lightDir), 0.0);
                vec4 diffuse = dotProduct * lights[i].diffuseColor * attenuation;

                float spec = 0.0;
                if(dotProduct > 0.0){
                    vec3 viewDir = normalize(cameraPos - worldPos3);
                    vec3 reflectDir = reflect(-lightDir, norm);  // fázovaný odrazový vektor
                    spec = pow(max(dot(viewDir, reflectDir), 0.0), lights[i].shiness);
                }
                vec4 specular = lights[i].specularIntensity * spec * lights[i].lightColor * attenuation;
                specular *= dotProduct;
                finalColor += diffuse + specular;
            }
        }


    }

    outColor = finalColor;
}
