#pragma once
#include "transformation.h"
#include <cstdlib> 
#include <ctime>
#include <vector>

class Translation : public Transformation {
private:
	glm::vec3 offset;
public:
	Translation(const glm::vec3 offset);
	glm::mat4 apply(const glm::mat4& matrix) override;
};


class RandomTranslation : public Transformation {
private:
    float speed; 
    glm::vec3 direction; 
    int stepsRemaining;
    int maxSteps;
    glm::vec3 added;
   
    glm::vec3 randomDirection();

public:
    RandomTranslation(float speed, int maxSteps);
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


class CostumTransformation : public Transformation {
private:
    glm::mat4x4 matrix;
public:
    CostumTransformation(const glm::mat4x4& matrix);
    glm::mat4 apply(const glm::mat4& matrix) override;
};

class RandomLine : public Transformation {
private:
    glm::vec3 A;
    glm::vec3 u;
    float t;
    float speed;

    glm::vec3 randomPoint();
    glm::vec3 randomDir();

public:
    RandomLine(float speed);
    glm::mat4 apply(const glm::mat4& matrix) override;
};




class Bezier : public Transformation {
private:
    glm::mat4 A;
    glm::mat4x3 B;
    float t;
    float speed;
    bool finished;

public:
    Bezier(const glm::vec3 controlPoints[4], float speed);
    glm::mat4 apply(const glm::mat4& matrix) override;
    bool isFinished() const { return finished; }
    void resetFinished() { finished = false; t = 0.0f; }
    float getT() const  { return t; }
};



class BezierCustom : public Transformation {
private:
    std::vector<glm::vec3> points;
    std::vector<Bezier> segments;
    int currentSegment = 0;

public:
    BezierCustom(const std::vector<glm::vec3>& points, float speed);
    glm::mat4 apply(const glm::mat4& matrix) override;

private:
    bool segmentFinished(const Bezier& b);
};