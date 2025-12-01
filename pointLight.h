#pragma once
#include "Light.h"

class pointLight : public Light {
    float attenuation;          
    glm::vec3 defaultPosition;    
    glm::vec3 positionSend;      

public:
        pointLight(const glm::vec3& pos,float intensity,float atten);
        pointLight(Model* m, ShaderProgram* sp, const glm::vec3& pos, float intensity,float atten);
        ~pointLight() {};
        LightData getLightData() const override;
        void Update() override;
};