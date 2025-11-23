#pragma once
#include "Light.h"

class directLight : public Light {
private:
	glm::vec3 direction;
public:
    directLight(const glm::vec3& direction,
        
        float intensity
        );

    ~directLight() {};
    LightData getLightData() const override;
    void Update() override;
};


