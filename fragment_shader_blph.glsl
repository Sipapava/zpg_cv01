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

        if (lights[i].type == 1) {
            // Pouze ambientní svìtlo
         finalColor += lights[i].ambientColor;
        }
       
     
        if (lights[i].type == 2) {
            vec3 lightDir = normalize(-lights[i].direction); // svìtlo dopadá z direction smìrem k objektu
            vec3 norm = normalize(worldNormal);

            float diff = max(dot(norm, lightDir), 0.0);
            vec4 diffuse = diff * lights[i].diffuseColor;

            float spec = 0.0;
            if (diff > 0.0) {
                vec3 viewDir = normalize(cameraPos - worldPosition.xyz);
                vec3 halfwayDir = normalize(lightDir + viewDir);
                spec = pow(max(dot(norm, halfwayDir), 0.0), lights[i].shiness);
            }

            vec4 specular = lights[i].specularIntensity * spec * lights[i].lightColor;

            finalColor +=  diffuse + specular;
        }

     
        if(lights[i].type == 3){
          
            vec3 worldPos3 = worldPosition.xyz / worldPosition.w;
            vec3 lightToVector = lights[i].lightPosition - worldPos3;
            float distance = length(lightToVector);
            float attenuation  = 1.0 / (1.0 + (lights[i].attenuation * distance) + (lights[i].attenuation * distance * distance));

            float dotProduct = smoothstep(0.0, 1.0,
                               dot(normalize(lightToVector), normalize(worldNormal)));
            vec4 diffuse = dotProduct * lights[i].diffuseColor;

            float spec = 0.0;
            if (dotProduct > 0.0) {
                vec3 viewDir = normalize(cameraPos - worldPosition.xyz);
                vec3 halfwayDir = normalize(normalize(lightToVector) + normalize(viewDir));
                spec = pow(max(dot(worldNormal, halfwayDir), 0.0), lights[i].shiness);
            }

            vec4 specular = lights[i].specularIntensity * spec * lights[i].lightColor;
            specular *= dotProduct;

            diffuse *= attenuation;
            specular *= attenuation;
            finalColor += diffuse + specular;
        }

        if (lights[i].type == 4) { // spotlight
    vec3 worldPos3 = worldPosition.xyz / worldPosition.w;
    vec3 lightDir = normalize(lights[i].lightPosition - worldPos3); // smìr k pixelu
    vec3 spotDir = normalize(-lights[i].direction);                 // smìr kužele

    float theta = dot(lightDir, spotDir);                            // úhel mezi pixel a osou kužele
    float epsilon = cos(lights[i].angleReflector);                  // cutoff úhel

   

if (theta > epsilon) {  // pixel je uvnitø kužele
    float distance = length(lights[i].lightPosition - worldPos3);
    float attenuation = 1.0 / (1.0 + lights[i].attenuation * distance + lights[i].attenuation * distance * distance);

    vec3 norm = normalize(worldNormal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * lights[i].diffuseColor * attenuation;

    float spec = 0.0;
    if(diff > 0.0){
        vec3 viewDir = normalize(cameraPos - worldPosition.xyz);
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(norm, halfwayDir), 0.0), lights[i].shiness);
    }
    vec4 specular = lights[i].specularIntensity * spec * lights[i].lightColor * attenuation;

    finalColor += diffuse + specular;
}
}

    

    }

    outColor = finalColor;
}
