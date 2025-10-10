#include "camera.h"

Camera::Camera() {
    // Doplnit v�choz� hodnoty atribut�
    position = glm::vec3(-0.7f, -0.3f, -0.2f);  // kousek dozadu na Z, aby nebyla uvnit� stromu
    target = glm::vec3(-0.7f, 0.0f, 0.0f);    // kouk� nahoru pod�l kmene
    up = glm::vec3(0.0f, 0.0f, 1.0f);     // osa Z jako "up", aby nebyl obraz oto�en�
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
    
    // Ozna�en� shader�, �e je pot�eba aktualizovat uniformy
    for (auto* sp : shaderPrograms) {
        sp->UpdateCamera();
    }
}
