#include "camera.h"


#include <glm/gtc/constants.hpp>

Camera::Camera() {
  
    position = glm::vec3(0.0f, 0.5f, -2.0f);
    target = glm::vec3(0.0f, 0.0f, 0.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
 
    fov = 45.0f;
    aspect = 800.0f / 600.0f;
    nearPlane = 0.1f;
    farPlane = 100.0f;

    resolutionY = 600;
    
    CameraData camData; //matrix
};

Camera::~Camera() {};

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, target, up);
}
glm::mat4 Camera::getProjectionMatrix() {
    return  glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}

void Camera::UpdateMatrix() {
    glm::mat4 Mp = this->getProjectionMatrix();
    glm::mat4 Mv = this->getViewMatrix();

    NotifyObservers(NotifyType::CameraPos, &position);

    camData = { Mv, Mp };
    NotifyObservers(NotifyType::CameraMatrix, &camData);
}


void Camera::setAspect(float aspect) {
    this->aspect = aspect;
    this->UpdateMatrix();
}

void Camera::SetResolutionY(int y) {
    this->resolutionY = y;  
}


int Camera::GetResolutionY() {
    return this->resolutionY;
}

void Camera::setAttachedReflectors()
{
    for (Observer* obs : observers)
    {
        if (auto* reflector = dynamic_cast<reflectorLightCamera*>(obs))
        {
            reflector->TurnOnOff();   
        }
    }
}


//camera goes forawrd everytime reative to eye target

const float CAMERA_SPEED = 0.02f; 

void Camera::moveForward() {
    glm::vec3 direction = glm::normalize(target - position); //calculate direction and normalize
    position += direction * CAMERA_SPEED; 
    target += direction * CAMERA_SPEED;
    this->UpdateMatrix();
   
}

void Camera::moveBackward() {
    glm::vec3 direction = glm::normalize(target - position);
    position -= direction * CAMERA_SPEED;
    target -= direction * CAMERA_SPEED;
    this->UpdateMatrix();
}

void Camera::moveLeft() {
    glm::vec3 direction = glm::normalize(target - position);
    glm::vec3 right = glm::normalize(glm::cross(direction,up));
    position -= right * CAMERA_SPEED;
    target -= right * CAMERA_SPEED;
    this->UpdateMatrix();
}

void Camera::moveRight() {
    glm::vec3 direction = glm::normalize(target - position);
    glm::vec3 right = glm::normalize(glm::cross(direction,up)); 
    position += right * CAMERA_SPEED;
    target += right * CAMERA_SPEED;
    this->UpdateMatrix();
}



void Camera::adjustTarget(double xOffsetMouse, double yOffsetMouse) {
    const float sensitivity = 0.1f;
    xOffsetMouse *= sensitivity;
    yOffsetMouse *= sensitivity;

    
    glm::vec3 forward = glm::normalize(target - position); //direction
    float alfa = glm::degrees(asin(forward.y));
    float fi = glm::degrees(atan2(forward.z, forward.x));
    //atan2 distinguishes the right and left halves of the x axis, returns the range (-180 - 180)

    
    fi += (float)xOffsetMouse;
    alfa -= (float)yOffsetMouse; //minus dat

    
    if (fi > 179.9f)  fi = -179.9f; //limiting the return values ??of gon.functions
    if (fi < -179.9f) fi = +179.9f;
   
    
    if (alfa > 89.0f)  alfa = 89.9f;
    if (alfa < -89.0f) alfa = -89.9f;

    
    glm::vec3 direction;
    direction.x = cos(glm::radians(fi)) * cos(glm::radians(alfa));
    direction.y = sin(glm::radians(alfa));
    direction.z = sin(glm::radians(fi)) * cos(glm::radians(alfa));

    target = position + glm::normalize(direction);
    this->UpdateMatrix();
}





