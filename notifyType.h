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
    glm::vec3 position;
    glm::vec4 color;
    float intensity;
    float shininess;
};

struct ShaderLightSlot {
    LightData data;   // vlastní data svìtla
    bool updated;     // flag, zda bylo zmìnìno a je tøeba aktualizovat shader
};
//CameraPosje jen vector 3