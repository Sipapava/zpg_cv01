#pragma once
#include <vector>
#include "shaderProgram.h"
#include "drawableObject.h"

class Scene {
private:
    ShaderProgram* shaderProgram;                 // shader, který používá scéna
    std::vector<DrawableObject*> drawableObjects; // ukazatele na objekty

public:
    Scene(ShaderProgram* shader);
    ~Scene();

    void addDrawableObject(DrawableObject* obj);
    void draw();
};
