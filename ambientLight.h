#pragma once
#include "Light.h"

class ambientLight : public Light {
private:
	glm::vec4 ambientColor;

public:
    ambientLight(   const glm::vec4& colorAmbient);

    ~ambientLight() {};
    LightData getLightData() const override;
    void Update() override;
};