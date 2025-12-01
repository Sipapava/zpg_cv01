#pragma once
#include "light.h"
#include "Observer.h"

class reflectorLight : public Light { 
protected:
	glm::vec3 direction;
	glm::vec3 defaultPosition;    
	glm::vec3 positionSend;
	float angle;
	float attenuation;
  

public:
    reflectorLight(const glm::vec3& pos, const glm::vec3& dir,float intensity,float atten, float angle);
    ~reflectorLight() {};
    LightData getLightData() const override;
    void Update() override;

};


// ---------------------------------------------------------------------------------


class reflectorLightCamera : public reflectorLight, public Observer {
private:
    glm::mat4* Mv;
    bool turnOn;

public:
    reflectorLightCamera(const glm::vec3& pos, const glm::vec3& dir,
        

        float intensity,
        
        float atten, float angle);

    ~reflectorLightCamera() {};
    LightData getLightData() const override;
    void Update() override;
    void Notify(NotifyType type, void* data);
    void TurnOnOff();
};