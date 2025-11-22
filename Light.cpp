#include "Light.h"


Light::Light(const glm::vec4& colorSpecular, float intensity, float shiness, const glm::vec4& colorDiffuse)
    : DrawableObject(nullptr, nullptr,"light"),
    colorSpecular(colorSpecular),
    specularIntesity(intensity),
    shiness(shiness),
    diffuseColor(colorDiffuse)
{
    
}


Light::Light(Model* m, ShaderProgram* sp,
    const glm::vec4& colorSpecular, float intensity, float shiness, const glm::vec4& colorDiffuse)
    : DrawableObject(m, sp,"light"),
    colorSpecular(colorSpecular),
    specularIntesity(intensity),
    shiness(shiness),
    diffuseColor(colorDiffuse)
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