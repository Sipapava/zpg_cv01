#pragma once
#include "light.h"
#include "Observer.h"

class reflectorLight : public Light, public Observer { 
private:
	glm::vec3 direction;
    glm::vec3 directionSend;
	glm::vec3 defaultPosition;    
	glm::vec3 positionSend;
	float angle;
	float attenuation;
    glm::mat4* Mv;

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
    void Notify(NotifyType type, void* data);
};