#include "ambientLight.h"

ambientLight::ambientLight(const glm::vec4& colorAmbient) : Light(  
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        0.0f,
        0.0f,
    glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
    ambientColor(colorAmbient)
{
    
}



void ambientLight::Update() {
    /*
    glm::mat4 I = glm::mat4(1.0f);
    glm::mat4 M = this->transformation->apply(I);

    glm::vec4 oldPos = glm::vec4(defaultPosition, 1.0f);
    glm::vec4 newPos = M * oldPos;




    if (!glm::all(glm::epsilonEqual(newPos, glm::vec4(positionSend, 1.0f), 0.0005f))) {
        positionSend = glm::vec3(newPos);

        UpdateLightsShaderPro();
    }

    */
}


LightData ambientLight::getLightData() const {
    LightData data;
    data.id = id;
    data.type = 1;
    data.position = glm::vec3(0.0f, 0.0f, 0.0f);
  ;
    data.intensity = specularIntesity;
   
    data.attenuation = 0.0f;
  

    data.angleReflector = 0.0f;
    data.direction = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    return data;
}
