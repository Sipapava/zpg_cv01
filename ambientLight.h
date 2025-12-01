#pragma once
#include "Light.h"

class ambientLight : public Light {
public:
    ambientLight();
    ~ambientLight() {};
    LightData getLightData() const override;
    void Update() override;
};