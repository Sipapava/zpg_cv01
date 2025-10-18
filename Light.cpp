#include "Light.h"

int Light::nextId = 0;
Light::Light(const glm::vec3& position, const glm::vec4& color, float intesnity,float shiness)
    : position(position), color(color), specularIntesity(intesnity),shiness(shiness){

    id = nextId++;
}

void Light::UpdateLightsShaderPro() {
    this->NotifyObservers(position, color,specularIntesity,shiness);
    
}

