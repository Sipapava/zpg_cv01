#include "Light.h"


Light::Light(float intensity) : DrawableObject(nullptr, nullptr,"light"),specularIntesity(intensity)
{
    
}


Light::Light(Model* m, ShaderProgram* sp,float intensity) : DrawableObject(m, sp,"light"),specularIntesity(intensity)   
{
    
}


void Light::UpdateLightsShaderPro() {
    LightData lightData = this->getLightData();
    NotifyObservers(NotifyType::LightChange, &lightData);
}




void Light::Update() {
   
}


void Light::AddObserver(Observer* o) {
    subject::AddObserver(o);
    NotifyObserver(o, NotifyType::SpRegisterLight, this);
}

void Light::RemoveObserver(Observer* o) {
    subject::RemoveObserver(o);
    NotifyObserver(o, NotifyType::SpUnfollowLight, this);
}

LightData Light::getLightData() const {
    LightData data;
    return data;
}