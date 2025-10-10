#pragma once
#include "shaderProgram.h"
#include<vector>

class ShaderProgram;
class Camera {
private:
    std::vector<ShaderProgram*> shaderPrograms;
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    float fov;
    float aspect;
    float nearPlane;
    float farPlane;

   
public:
    Camera();
    ~Camera();
    void Update();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    //v konstruktoru vychozi pohled nastavime
    //controller kdyz se pohne zavola setter na atributy, ty ze zmeni a udela se prislusny notify
    //notify metoda()
        //zavola SetUniform na mych novych projektivni a view matici
};