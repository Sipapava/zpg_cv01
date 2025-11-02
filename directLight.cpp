#include "directLight.h"

directLight::directLight(const glm::vec3& direction,
    const glm::vec4& colorSpecular,
    const glm::vec4& colorDiffuse,
    float intensity,
    float shininess)
    : Light(colorSpecular, intensity, shininess, colorDiffuse),
    direction(direction)
{
   
}
//kosntruktor po obejkt
void directLight::Update() {
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


LightData directLight::getLightData() const {
    LightData data;
    data.id = id;
    data.type = 2;
    data.position = glm::vec3(0.0f, 0.0f, 0.0f);
    data.colorSpecular = colorSpecular;
    data.intensity = specularIntesity;
    data.shininess = shiness;
    data.diffuseColor = diffuseColor;
    data.attenuation = 0.0f;
    data.ambientColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    data.angleReflector = 0.0f;
    data.direction = direction;
    return data;
}