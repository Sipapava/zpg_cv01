#include "directLight.h"

directLight::directLight(const glm::vec3& direction,float intensity) : Light( intensity),direction(direction)
{}

void directLight::Update() {}


LightData directLight::getLightData() const {
    LightData data;
    data.id = id;
    data.type = 2;
    data.position = glm::vec3(0.0f, 0.0f, 0.0f);
    data.intensity = specularIntesity;
    data.attenuation = 0.0f;
    data.angleReflector = 0.0f;
    data.direction = direction;
    return data;
}