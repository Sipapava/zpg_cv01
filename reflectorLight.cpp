#include "reflectorLight.h"

reflectorLight::reflectorLight(const glm::vec3& pos, const glm::vec3& dir,
    const glm::vec4& colorSpecular,
    const glm::vec4& colorDiffuse,
    float intensity,
    float shininess,
    float atten,float angle)
    : Light(colorSpecular, intensity, shininess, colorDiffuse), // zavolá konstruktor Light
    defaultPosition(pos),     // inicializuje vlastní atributy
    positionSend(pos),
    attenuation(atten),
    direction(dir),angle(angle)
{
    // tady mùžeš udìlat další inicializace, pokud je potøeba
}


void reflectorLight::Update() {
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


LightData reflectorLight::getLightData() const {
    LightData data;
    data.id = id;
    data.type = 4;
    data.position = positionSend;
    data.colorSpecular = colorSpecular;
    data.intensity = specularIntesity;
    data.shininess = shiness;
    data.diffuseColor = diffuseColor;
    data.attenuation = attenuation;
    data.ambientColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    data.angleReflector = angle;
    data.direction = direction;
    return data;
}
