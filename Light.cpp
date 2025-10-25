#include "Light.h"

int Light::nextId = 0;
Light::Light(const glm::vec3& position, const glm::vec4& color, float intesnity,float shiness)
    : position(position), color(color), specularIntesity(intesnity),shiness(shiness){

    id = nextId++;
}

void Light::UpdateLightsShaderPro() {
    LightData lightData;
    lightData.id = this->id;
    lightData.position = this->position;          // glm::vec3
    lightData.color = this->color;               // glm::vec4
    lightData.intensity =this->specularIntesity; 
    lightData.shininess = this->shiness;

    NotifyObservers(NotifyType::LightChange, &lightData);
}



void Light::AddObserver(Observer* o) {
    // nejd��ve p�id�me do seznamu
    Subject::AddObserver(o);

    // vytvo��me data s id sv�tla
    NotifyObserver(o, NotifyType::SpRegisterLight, this);

 
}

void Light::RemoveObserver(Observer* o) {
    // odstran�me ze seznamu
    // zavol�me z�kladn� implementaci (odstran� ze seznamu)
    Subject::RemoveObserver(o);

    // p�ed�me shaderu zpr�vu o odhl�en�
    
    NotifyObserver(o, NotifyType::SpUnfollowLight, this);
   
}

LightData Light::getLightData() const {
    LightData data;
    data.id = id;               // ID sv�tla
    data.position = position;   // pozice
    data.color = color;         // barva (diffuse)
    data.intensity = specularIntesity; // intenzita/specular
    data.shininess = shiness;   // lesklost
    return data;
}