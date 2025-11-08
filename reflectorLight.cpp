#include "reflectorLight.h"

reflectorLight::reflectorLight(const glm::vec3& pos, const glm::vec3& dir,
    const glm::vec4& colorSpecular,
    const glm::vec4& colorDiffuse,
    float intensity,
    float shininess,
    float atten, float angle)
    : Light(colorSpecular, intensity, shininess, colorDiffuse),
    defaultPosition(pos),     
    positionSend(pos),
    attenuation(atten),
    direction(dir), angle(angle)
{
   
}

void reflectorLight::Update() {
    /*
    if (!Mv) return; 

   
    glm::vec3 forward;
    forward.x = -(*Mv)[0][2];
    forward.y = -(*Mv)[1][2];
    forward.z = -(*Mv)[2][2];
    forward = glm::normalize(forward);

    glm::vec3 newPosition = positionSend; 
    glm::vec3 newDirection = forward;     

   
    bool positionChanged = !glm::all(glm::epsilonEqual(newPosition, positionSend, 0.0005f));
    bool directionChanged = !glm::all(glm::epsilonEqual(newDirection, direction, 0.0005f));

    if (positionChanged || directionChanged) {
        positionSend = newPosition;
        direction = newDirection;

        
        UpdateLightsShaderPro();
    }
    */
}


LightData reflectorLight::getLightData() const {
    LightData data;
    data.id = id;
    data.type = 4;
    data.position = positionSend;
    data.colorSpecular = colorSpecular;
    data.intensity = specularIntesity;
    data.shininess = shiness;
    data.diffuseColor = diffuseColor;
    data.attenuation = attenuation;
    data.ambientColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    data.angleReflector = angle;
    data.direction = direction;
    return data;
}



//---------------------------------------------------------------------------------------------------


reflectorLightCamera::reflectorLightCamera(
    const glm::vec3& pos, const glm::vec3& dir,
    const glm::vec4& colorSpecular,
    const glm::vec4& colorDiffuse,
    float intensity,
    float shininess,
    float atten,
    float angle)
    : reflectorLight(pos, dir, colorSpecular, colorDiffuse, intensity, shininess, atten, angle),
    Mv(nullptr),
    turnOn(true)
{
}

void reflectorLightCamera::Update() {
    if (!Mv) return;


    glm::vec3 forward;
    forward.x = -(*Mv)[0][2];
    forward.y = -(*Mv)[1][2];
    forward.z = -(*Mv)[2][2];
    forward = glm::normalize(forward);

  
    glm::vec3 newDirection = forward;


    bool positionChanged = !glm::all(glm::epsilonEqual(defaultPosition, positionSend, 0.0005f));
    bool directionChanged = !glm::all(glm::epsilonEqual(newDirection, direction, 0.0005f));

    if (positionChanged || directionChanged) {
        defaultPosition = positionSend;
        direction = newDirection;


        UpdateLightsShaderPro();
    }
}


LightData reflectorLightCamera::getLightData() const {
    LightData data;
    data.id = id;
    data.type = 4;
    data.position = positionSend;
    data.angleReflector = angle;
    data.direction = direction;

    if (turnOn) {

       
        data.colorSpecular = colorSpecular;
        data.intensity = specularIntesity;
        data.shininess = shiness;
        data.diffuseColor = diffuseColor;
        data.attenuation = attenuation;
        data.ambientColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

        
        

    }
    else {
        
        data.colorSpecular = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        data.intensity = specularIntesity;
        data.shininess = shiness;
        data.diffuseColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        data.attenuation = attenuation;
        data.ambientColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

       

    }
    return data;
   
}


void reflectorLightCamera::Notify(NotifyType type, void* data) {
    switch (type) {
    case NotifyType::CameraMatrix: {
        CameraData* camData = static_cast<CameraData*>(data);
        Mv = &camData->view;
        break;
    }
    case NotifyType::CameraPos: {
        glm::vec3* camPos = static_cast<glm::vec3*>(data);
        this->positionSend = *camPos;

        break;
    }

    case NotifyType::LightChange: {

        break;
    }
    case NotifyType::SpRegisterLight: {

        break;
    }

    case NotifyType::SpUnfollowLight: {

        break;
    }

    default:
        break;
    }
}

void reflectorLightCamera::TurnOnOff() {
    this->turnOn = !this->turnOn;
    UpdateLightsShaderPro();
}