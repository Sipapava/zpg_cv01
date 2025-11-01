#pragma once
#include "Light.h"

class directLight : public Light {
private:
	glm::vec3 direction;
public:
    directLight(const glm::vec3& direction,
        const glm::vec4& colorSpecular,
        const glm::vec4& colorDiffuse,
        float intensity,
        float shininess);

    ~directLight() {};
    LightData getLightData() const override;
    void Update() override;
};


