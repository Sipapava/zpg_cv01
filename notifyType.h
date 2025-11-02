#pragma once
#include "glm/glm.hpp"

enum class NotifyType {
    CameraMatrix,
    CameraPos,
    LightChange,
    SpRegisterLight,
    SpUnfollowLight
};


struct CameraData {
    glm::mat4 view;
    glm::mat4 projection;
};



struct LightData {
    int id;
    int type;
    glm::vec3 position;
    glm::vec3 direction;
    float angleReflector;
    glm::vec4 colorSpecular;
    float intensity;
    float shininess;
    glm::vec4 diffuseColor;
    float attenuation;
    glm::vec4 ambientColor;

};

struct ShaderLightSlot {
    LightData data;  
    bool updated;     
};
