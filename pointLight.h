#pragma once
#include "Light.h"

class pointLight : public Light {
    float attenuation;            // tlumení svìtla s vzdáleností
    glm::vec3 defaultPosition;    // výchozí pozice
    glm::vec3 positionSend;       // pozice, která se posílá do shaderu

public:
        pointLight(const glm::vec3& pos,
        const glm::vec4& colorSpecular,
        const glm::vec4& colorDiffuse,
        float intensity,
        float shininess,
        float atten);

        pointLight(Model* m, ShaderProgram* sp, const glm::vec3& pos,
            const glm::vec4& colorSpecular,
            const glm::vec4& colorDiffuse,
            float intensity,
            float shininess,
            float atten);

       

        ~pointLight() {};
        LightData getLightData() const override;
        void Update() override;
};