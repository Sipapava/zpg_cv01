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
    // nejdøíve pøidáme do seznamu
    Subject::AddObserver(o);

    // vytvoøíme data s id svìtla
    NotifyObserver(o, NotifyType::SpRegisterLight, this);

 
}

void Light::RemoveObserver(Observer* o) {
    // odstraníme ze seznamu
    // zavoláme základní implementaci (odstraní ze seznamu)
    Subject::RemoveObserver(o);

    // pøedáme shaderu zprávu o odhlášení
    
    NotifyObserver(o, NotifyType::SpUnfollowLight, this);
   
}

LightData Light::getLightData() const {
    LightData data;
    data.id = id;               // ID svìtla
    data.position = position;   // pozice
    data.color = color;         // barva (diffuse)
    data.intensity = specularIntesity; // intenzita/specular
    data.shininess = shiness;   // lesklost
    return data;
}