#include "camera.h"

#include <glm/gtc/constants.hpp>

Camera::Camera(std::vector<ShaderProgram*>* shaderprograms) : shaderPrograms(shaderprograms) {
  
    position = glm::vec3(0.0f, 0.5f, -2.0f);
    target = glm::vec3(0.0f, 0.0f, 0.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);

    fov = 45.0f;
    aspect = 800.0f / 600.0f;
    nearPlane = 0.1f;
    farPlane = 100.0f;
};

Camera::~Camera() {};

glm::mat4 Camera::getViewMatrix() {

    return glm::lookAt(position, target, up);
}
glm::mat4 Camera::getProjectionMatrix() {
    return  glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}

void Camera::Update() {
    
    for (auto sp : *shaderPrograms) {
        sp->UpdateCamera();
    }
}

//kamera jde dopredu vzdy relativne k eyeTargetu

const float CAMERA_SPEED = 0.02f; 

void Camera::moveForward() {
    glm::vec3 direction = glm::normalize(target - position); //spocita vektor smer a notmalizuje na jendotku
    position += direction * CAMERA_SPEED; //jen pricteme k position a vynasobime pohybem
    target += direction * CAMERA_SPEED;
    this->Update();
}

void Camera::moveBackward() {
    glm::vec3 direction = glm::normalize(target - position);
    position -= direction * CAMERA_SPEED;
    target -= direction * CAMERA_SPEED;
    this->Update();
}

void Camera::moveLeft() {
    glm::vec3 direction = glm::normalize(target - position);
    glm::vec3 right = glm::normalize(glm::cross(direction,up));
    position -= right * CAMERA_SPEED;
    target -= right * CAMERA_SPEED;
    this->Update();
}

void Camera::moveRight() {
    glm::vec3 direction = glm::normalize(target - position);
    glm::vec3 right = glm::normalize(glm::cross(direction,up)); 
    position += right * CAMERA_SPEED;
    target += right * CAMERA_SPEED;
    this->Update();
}



void Camera::adjustTarget(double xOffsetMouse, double yOffsetMouse) {
    const float sensitivity = 0.1f;
    xOffsetMouse *= sensitivity;
    yOffsetMouse *= sensitivity;

    
    glm::vec3 forward = glm::normalize(target - position);
    float alfa = glm::degrees(asin(forward.y));
    float fi = glm::degrees(atan2(forward.z, forward.x));
    //atan2 rozlisi pravou a levou pulku x osy, vraci rozsah (-180 - 180)

    
    fi += (float)xOffsetMouse;
    alfa += (float)yOffsetMouse;

    
    if (fi > 179.9f)  fi = -179.9f; //omezeni navratovych hodnot gon. funkci
    if (fi < -179.9f) fi = +179.9f;
   
    
    if (alfa > 89.0f)  alfa = 89.9f;
    if (alfa < -89.0f) alfa = -89.9f;

    
    glm::vec3 direction;
    direction.x = cos(glm::radians(fi)) * cos(glm::radians(alfa));
    direction.y = sin(glm::radians(alfa));
    direction.z = sin(glm::radians(fi)) * cos(glm::radians(alfa));

    target = position + glm::normalize(direction);
    this->Update();
}





