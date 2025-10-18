#pragma once
#include "shaderProgram.h"
#include<vector>
#include "Subject.h"
#include "Observer.h"
#include "glm/glm.hpp"


class Camera : public Subject {
private:
    
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    float fov;
    float aspect;
    float nearPlane;
    float farPlane;
    

   
public:
    Camera(std::vector<ShaderProgram*>* shaderprograms);
    ~Camera();
    void UpdateMatrix();
    
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    void adjustTarget(double xOffsetMouse, double yOffsetMouse);
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();

};