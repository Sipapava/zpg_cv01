#pragma once
#include "light.h"

class reflectorLight : public Light {
private:
	glm::vec3 direction;
	glm::vec3 defaultPosition;    // výchozí pozice
	glm::vec3 positionSend;
	float angle;
	float attenuation;

public:
    reflectorLight(const glm::vec3& pos, const glm::vec3& dir,
        const glm::vec4& colorSpecular,
        const glm::vec4& colorDiffuse,
     
        float intensity,
        float shininess,
        float atten, float angle);

    ~reflectorLight() {};
    LightData getLightData() const override;
    void Update() override;
};