#version 330 core

in vec4 fragColor;
in vec4 worldPosition;
in vec3 worldNormal;
in vec2 textCoords;
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
uniform sampler2D texture_test;
uniform vec4 color;

void main()
{
    vec4 finalColor = vec4(0.0);
  
   

    for (int i = 0; i < numberOfLights && i < MAX_LIGHTS; ++i) {

        if (lights[i].type == 1) {
             finalColor += lights[i].ambientColor;
        }
       
     
        if (lights[i].type == 2) {
            vec3 lightDir = normalize(-lights[i].direction); // smer od fragmentu ke svetlu
            vec3 norm = normalize(worldNormal);

            float dotProduct = smoothstep(0.0, 1.0, dot(lightDir, norm));
            vec4 diffuse = dotProduct * lights[i].diffuseColor;

            float spec = 0.0;
            if (dotProduct > 0.0) {

                 vec3 worldPos3 = vec3(
                        worldPosition.x / worldPosition.w,
                        worldPosition.y / worldPosition.w,
                        worldPosition.z / worldPosition.w);
                vec3 viewDir = normalize(cameraPos - worldPos3);
                vec3 halfwayDir = normalize(lightDir + viewDir);
                spec = pow(max(dot(norm, halfwayDir), 0.0), lights[i].shiness);
            }

            vec4 specular = lights[i].specularIntensity * spec * lights[i].lightColor;
            specular *= dotProduct;
            finalColor +=  diffuse + specular;
        }

     
        if(lights[i].type == 3){
          
             vec3 worldPos3 = vec3(
                        worldPosition.x / worldPosition.w,
                        worldPosition.y / worldPosition.w,
                        worldPosition.z / worldPosition.w);
            vec3 lightToVector = lights[i].lightPosition - worldPos3;
            float distance = length(lightToVector);
            float attenuation  = 1.0 / (1.0 + (lights[i].attenuation * distance) + (lights[i].attenuation * distance * distance));

            float dotProduct = smoothstep(0.0, 1.0,
                               dot(normalize(lightToVector), normalize(worldNormal)));
            vec4 diffuse = dotProduct * lights[i].diffuseColor;

            float spec = 0.0;
            if (dotProduct > 0.0) {
                vec3 viewDir = normalize(cameraPos - worldPos3 );
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
            vec3 worldPos3 = vec3(
                        worldPosition.x / worldPosition.w,
                        worldPosition.y / worldPosition.w,
                        worldPosition.z / worldPosition.w);
            vec3 lightDir = normalize(lights[i].lightPosition - worldPos3); // odraz od fragmentu k pozici svetla
            vec3 spotDir = normalize(-lights[i].direction);                 // smer reflectoru

            float theta = dot(lightDir, spotDir);                            // uhel os a kuzele a svetla
            float epsilon = cos(lights[i].angleReflector);                  // cutoff uhel, polovina refelcotove oblasti

   

            if (theta > epsilon) {  // hodnota cos rostes mensim uhlem
                float distance = length(lights[i].lightPosition - worldPos3);
                float attenuation = 1.0 / (1.0 + lights[i].attenuation * distance + lights[i].attenuation * distance * distance);

                vec3 norm = normalize(worldNormal);
                float dotProduct  = max(dot(norm, lightDir), 0.0);
                vec4 diffuse = dotProduct  * lights[i].diffuseColor * attenuation;

                float spec = 0.0;
                if(dotProduct  > 0.0){
                    vec3 viewDir = normalize(cameraPos - worldPos3 );
                    vec3 halfwayDir = normalize(lightDir + viewDir);
                    spec = pow(max(dot(norm, halfwayDir), 0.0), lights[i].shiness);
                 }
                vec4 specular = lights[i].specularIntensity * spec * lights[i].lightColor * attenuation;
                specular *= dotProduct;

                finalColor += diffuse + specular;
            }
        }


    

    }
     vec4 texColor = texture(texture_test, textCoords); 
    
    if(texColor.a > 0.1)
        outColor = texColor * finalColor;
    else
        outColor =  finalColor * color; 
}
