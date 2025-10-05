#pragma once
#include "transformation.h"


class Translation : public Transformation {
private:
	glm::vec3 offset;
public:
	Translation(const glm::vec3 offset);
	glm::mat4 apply(const glm::mat4& matrix) override;
};





class Rotation : public Transformation {
protected:
    float angle;
    glm::vec3 axis;
public:
    Rotation(float angle, const glm::vec3& axis);
    glm::mat4 apply(const glm::mat4& matrix) override;
};

class RotationDynamic : public Rotation {
    float addAngle; 
public:
    RotationDynamic(float initialAngle, const glm::vec3& axis, float addAngle);

    glm::mat4 apply(const glm::mat4& matrix) override;
};

class Scale : public Transformation {
private:
    glm::vec3 factors;
public:
    Scale(const glm::vec3& factors);
    glm::mat4 apply(const glm::mat4& matrix) override;
};

