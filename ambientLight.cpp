#include "ambientLight.h"

ambientLight::ambientLight() : Light(0.0f) {}

void ambientLight::Update() {
   
}


LightData ambientLight::getLightData() const {
    LightData data;
    data.id = id;
    data.type = 1;
    data.position = glm::vec3(0.0f, 0.0f, 0.0f);
    data.intensity = specularIntesity;
    data.attenuation = 0.0f;
    data.angleReflector = 0.0f;
    data.direction = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    return data;
}
