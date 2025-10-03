#pragma once
#include "transformation.h"


class Translation : public Transformation {
private:
	glm::vec3 offset;
public:
	Translation(const glm::vec3 offset);
	glm::mat4 apply(const glm::mat4& matrix) const override;
};


class Rotation : public Transformation {
private:
    float angle;
    glm::vec3 axis;
public:
    Rotation(float angle, const glm::vec3& axis);
    glm::mat4 apply(const glm::mat4& matrix) const override;
};

class Scale : public Transformation {
private:
    glm::vec3 factors;
public:
    Scale(const glm::vec3& factors);
    glm::mat4 apply(const glm::mat4& matrix) const override;
};

