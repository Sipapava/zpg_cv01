#pragma once
#include "Light.h"

class ambientLight : public Light {
private:
	glm::vec4 ambientColor;

public:
    ambientLight(
        const glm::vec4& colorSpecular,
        const glm::vec4& colorDiffuse,
        const glm::vec4& colorAmbient,
        float intensity,
        float shininess
       );

    ~ambientLight() {};
    LightData getLightData() const override;
    void Update() override;
};