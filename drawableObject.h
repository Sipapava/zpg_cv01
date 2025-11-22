#pragma once
#include "ShaderProgram.h"
#include "Model.h"
#include "texture.h"
#include "elementarTransformation.h"
#include "complexTransformation.h"
#include "material.h"


class DrawableObject {
protected:
    int id;
    static int nextId;
    std::string type;

    Model* model;
    ShaderProgram* shaderProgram;

    Transformation* transformation;
    glm::vec3 position;
    glm::vec4 color;

    std::vector<Texture*> textures;
    Material* material;
    


public:
    DrawableObject(Model* m, ShaderProgram* sp, std::string type);
    virtual ~DrawableObject();
    int getId() const { return id; }
    void MoveTo(float x, float y, float z);
    void Resize(float x, float y, float z);
    void Rotate(float angle, float xA, float yA, float zA);
    void SetRotateAnimation(float addAngle, const glm::vec3& axis);
    void SetRandomMoveAnimation(float speed, int maxSteps);
    void moveOnLine(float speed);

    void setCustomTransformation(const glm::mat4x4& matrix);

    void setColor(const glm::vec4& color);
    void setMaterial(Material* m);
    std::string GetType();
   

    void AddTexture(Texture* texture);

    void Update();
    virtual void draw();
};
