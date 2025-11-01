#include "pointLight.h"

pointLight::pointLight(const glm::vec3& pos,
    const glm::vec4& colorSpecular,
    const glm::vec4& colorDiffuse,
    float intensity,
    float shininess,
    float atten)
    : Light(colorSpecular, intensity, shininess, colorDiffuse), // zavolá konstruktor Light
    defaultPosition(pos),     // inicializuje vlastní atributy
    positionSend(pos),
    attenuation(atten)
{
    // tady mùžeš udìlat další inicializace, pokud je potøeba
}

pointLight::pointLight(Model* m, ShaderProgram* sp,
    const glm::vec3& pos,
    const glm::vec4& colorSpecular,
    const glm::vec4& colorDiffuse,
    float intensity,
    float shininess,
    float atten)
    : Light(m, sp, colorSpecular, intensity, shininess, colorDiffuse),
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
    data.colorSpecular = colorSpecular;
    data.intensity = specularIntesity;
    data.shininess = shiness;
    data.diffuseColor = diffuseColor;
    data.attenuation = attenuation;
    data.ambientColor = glm::vec4(0.0f, 0.0f, 0.0f,1.0f);

    data.angleReflector = 0.0f;
    data.direction = glm::vec3(0.0f,0.0f,0.0f);
    return data;
}

