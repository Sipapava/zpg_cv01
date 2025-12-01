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
    float intensity;
    float attenuation;
};

struct ShaderLightSlot {
    LightData data;  
    bool updated;     
};
