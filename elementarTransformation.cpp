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




glm::vec3 RandomTranslation::randomDirection() {
   
    float x = (rand() % 200 - 100) / 100.0f;
    float y = (rand() % 200 - 100) / 100.0f;
    float z = (rand() % 200 - 100) / 100.0f;
    glm::vec3 v(x, y, z);
    if (v == glm::vec3(0)) v = glm::vec3(1, 0, 0); 
    return glm::normalize(v);
}


RandomTranslation::RandomTranslation(float speed, int maxSteps)
    : speed(speed), maxSteps(maxSteps), stepsRemaining(0), added(0.0f, 0.0f, 0.0f) {
   
    direction = randomDirection();
    stepsRemaining = maxSteps;
   
}

glm::mat4 RandomTranslation::apply(const glm::mat4& matrix) {
    if (stepsRemaining <= 0) {
        direction = randomDirection();
        stepsRemaining = maxSteps;
        
        
    }
    added += direction * speed;
    glm::mat4 result = glm::translate(matrix, added);
    stepsRemaining--;
    return result;
}




CostumTransformation::CostumTransformation(const glm::mat4x4& matrix) : Transformation(), matrix(matrix) {}

glm::mat4 CostumTransformation::apply(const glm::mat4& matrix) {
    return matrix * this->matrix;
};


glm::vec3 RandomLine::randomPoint() {
    float x = -5.0f + (rand() / (float)RAND_MAX) * 10.0f;
    float y = 0.1f;
    float z = -5.0f + (rand() / (float)RAND_MAX) * 10.0f;
    return glm::vec3(x, y, z);
}

glm::vec3 RandomLine::randomDir() {
    float x = -1.0f + (rand() / (float)RAND_MAX) * 2.0f;
    float y = 0.0f;
    float z = -1.0f + (rand() / (float)RAND_MAX) * 2.0f;
    glm::vec3 d(x, y, z);
    return glm::normalize(d);
}

RandomLine::RandomLine(float speed)
    : speed(speed), t(0.0f)
{
    A = randomPoint();
    u = randomDir();
}

glm::mat4 RandomLine::apply(const glm::mat4& matrix) {
    if (t >= 1.0f) {
        A = A + u;        // nový zaèátek je skuteèný konec pøedchozího pohybu
        u = randomDir(); // nový smìrový vektor
        t = 0.0f;
    }

    glm::vec3 pos = A + u * t;
    t += speed;

    return glm::translate(matrix, pos);
}
