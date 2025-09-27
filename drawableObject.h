#pragma once
#include "ShaderProgram.h"
#include "Model.h"

class DrawableObject {
private:
    Model* model;                // obsahuje VAO a VBO
    ShaderProgram* shaderProgram;
    //prijde sem nejaka matice, aby bylo mozne mit jeden model pro jeden typ objektu, apk jen upravovat pozice a velikosti matici

public:
    DrawableObject(Model* m, ShaderProgram* sp);
    ~DrawableObject();

    void draw();
};
