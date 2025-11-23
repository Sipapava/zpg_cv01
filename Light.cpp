#include "Light.h"


Light::Light(float intensity)
    : DrawableObject(nullptr, nullptr,"light"),
    specularIntesity(intensity)
{
    
}


Light::Light(Model* m, ShaderProgram* sp,
    float intensity)
    : DrawableObject(m, sp,"light"),
    
    specularIntesity(intensity)
    
   
{
    
}


void Light::UpdateLightsShaderPro() {
    LightData lightData = this->getLightData();

    NotifyObservers(NotifyType::LightChange, &lightData);
}




void Light::Update() {
    /*
    glm::mat4 I = glm::mat4(1.0f);
    glm::mat4 M = this->transformation->apply(I);

    glm::vec4 oldPos = glm::vec4(defaultPosition, 1.0f);
    glm::vec4 newPos = M * oldPos;

   

    
    if (!glm::all(glm::epsilonEqual(newPos, glm::vec4(positionSend, 1.0f), 0.0005f))) {
        positionSend = glm::vec3(newPos);
       
        UpdateLightsShaderPro();
    }
    */
   
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
    /*
    data.id = id;               
    data.position = positionSend;   
    data.colorSpecular = colorSpecular;        
    data.intensity = specularIntesity; 
    data.shininess = shiness;   
    data.diffuseColor = diffuseColor;
    data.attenuation = attenuation;
    data.ambientColor = ambientColor;
    */
    return data;
}