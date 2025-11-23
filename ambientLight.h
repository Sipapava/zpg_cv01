#pragma once
#include "Light.h"

class ambientLight : public Light {
private:

public:
    ambientLight();

    ~ambientLight() {};
    LightData getLightData() const override;
    void Update() override;
};