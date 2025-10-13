#include "elementarTransformation.h"


Translation::Translation(const glm::vec3 offset) : Transformation(), offset(offset) {}

glm::mat4 Translation::apply(const glm::mat4& matrix) {  
    return glm::translate(matrix, offset);
}

Rotation::Rotation(float angle, const glm::vec3& axis) : Transformation(), angle(angle), axis(axis) {}

glm::mat4 Rotation::apply(const glm::mat4& matrix)  {
    return glm::rotate(matrix, angle, axis);
}

Scale::Scale(const glm::vec3& factors) : Transformation(), factors(factors) {}

glm::mat4 Scale::apply(const glm::mat4& matrix) {
    return glm::scale(matrix, factors);
}

glm::mat4 RotationDynamic::apply(const glm::mat4& matrix) {
    angle += addAngle; // 
    return glm::rotate(matrix, angle, axis);
}


RotationDynamic::RotationDynamic(float initialAngle, const glm::vec3& axis, float addAngle)
    : Rotation(initialAngle, axis), addAngle(addAngle) {}

