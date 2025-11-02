#pragma once
#include "ShaderProgram.h"
#include "Model.h"

#include "elementarTransformation.h"
#include "complexTransformation.h"


class DrawableObject {
protected:
    int id;
    static int nextId;

    Model* model;
    ShaderProgram* shaderProgram;

    Transformation* transformation;
    glm::vec3 position;
    int rotation[3];
    glm::vec3 rotationAxis;
    bool updateColor;
    glm::vec4 color;
    


public:
    DrawableObject(Model* m, ShaderProgram* sp);
    virtual ~DrawableObject();
    int getId() const { return id; }
    void MoveTo(float x, float y, float z);
    void Resize(float x, float y, float z);
    void Rotate(float angle, float xA, float yA, float zA);
    void SetRotateAnimation(float addAngle, const glm::vec3& axis);
    void SetRandomMoveAnimation(float speed, int maxSteps);
    void setColor(const glm::vec4& color);

    void Update();
    void draw();
};
