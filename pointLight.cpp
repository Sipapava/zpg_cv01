#include "pointLight.h"

pointLight::pointLight(const glm::vec3& pos,
    
    float intensity,
    
    float atten)
    : Light( intensity),
    defaultPosition(pos),     
    positionSend(pos),
    attenuation(atten)
{
    
}

pointLight::pointLight(Model* m, ShaderProgram* sp,
    const glm::vec3& pos,
   
    float intensity,
    
    float atten)
    : Light(m, sp, intensity),
    defaultPosition(pos),
    positionSend(pos),
    attenuation(atten)
{}


void pointLight::Update(){
    
    glm::mat4 I = glm::mat4(1.0f);
    glm::mat4 M = this->transformation->apply(I);

    glm::vec4 oldPos = glm::vec4(defaultPosition, 1.0f);
    glm::vec4 newPos = M * oldPos;




    if (!glm::all(glm::epsilonEqual(newPos, glm::vec4(positionSend, 1.0f), 0.0005f))) {
        positionSend = glm::vec3(newPos);

        UpdateLightsShaderPro();
    }
    

}


LightData pointLight::getLightData() const {
    LightData data;
    data.id = id;
    data.type = 3;
    data.position = positionSend;

    data.intensity = specularIntesity;
    
    data.attenuation = attenuation;


    data.angleReflector = 0.0f;
    data.direction = glm::vec3(0.0f,0.0f,0.0f);
    return data;
}

