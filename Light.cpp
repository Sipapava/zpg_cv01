#include "Light.h"

int Light::nextId = 0;
Light::Light(const glm::vec3& position, const glm::vec4& colorSpecular, float intesnity,float shiness,const glm::vec4& colorDiffuse,float attenuation)
    : defaultPosition(position), colorSpecular(colorSpecular), specularIntesity(intesnity),shiness(shiness){

    id = nextId++;
    complexTransformation* complexTrans = new complexTransformation();
    transformation = complexTrans;
    this->positionSend = position;
    this->diffuseColor = colorDiffuse;
    this->attenuation = attenuation;
}

void Light::UpdateLightsShaderPro() {
    LightData lightData;
    lightData.id = this->id;
    lightData.position = this->positionSend;          
    lightData.colorSpecular = this->colorSpecular;              
    lightData.intensity =this->specularIntesity; 
    lightData.shininess = this->shiness;
    lightData.diffuseColor = this->diffuseColor;
    lightData.attenuation = this->attenuation;

    NotifyObservers(NotifyType::LightChange, &lightData);
}

void Light::MoveTo(float x, float y, float z) {
    glm::vec3 delta = glm::vec3(x, y, z);
    transformation->Add(new Translation(delta));

}

void Light::Rotate(float angle, float xA, float yA, float zA) {
    transformation->Add(new Rotation(angle, glm::vec3(xA, yA, zA)));

}

void Light::SetRotateAnimation(float addAngle, const glm::vec3& axis) {

    transformation->Add(new RotationDynamic(0.0f, axis, addAngle));

};


void Light::Update() {
    glm::mat4 I = glm::mat4(1.0f);
    glm::mat4 M = this->transformation->apply(I);

    glm::vec4 oldPos = glm::vec4(defaultPosition, 1.0f);
    glm::vec4 newPos = M * oldPos;

   

    
    if (!glm::all(glm::epsilonEqual(newPos, glm::vec4(positionSend, 1.0f), 0.0005f))) {
        positionSend = glm::vec3(newPos);
       
        UpdateLightsShaderPro();
    }
   
}


void Light::AddObserver(Observer* o) {
    
    Subject::AddObserver(o);

    
    NotifyObserver(o, NotifyType::SpRegisterLight, this);

 
}

void Light::RemoveObserver(Observer* o) {
    
    Subject::RemoveObserver(o);

  
    
    NotifyObserver(o, NotifyType::SpUnfollowLight, this);
   
}

LightData Light::getLightData() const {
    LightData data;
    data.id = id;               
    data.position = positionSend;   
    data.colorSpecular = colorSpecular;        
    data.intensity = specularIntesity; 
    data.shininess = shiness;   
    data.diffuseColor = diffuseColor;
    data.attenuation = attenuation;
    return data;
}