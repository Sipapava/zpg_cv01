#pragma once
#include "ShaderProgram.h"
#include "Model.h"

#include "elementarTransformation.h"
#include "complexTransformation.h"

class DrawableObject {
private:
    int id;                      
    static int nextId;
    //kompozice vs agregace otazka?,kompozici ne ale agregaci tady ano
    Model* model;                // obsahuje VAO a VBO
    ShaderProgram* shaderProgram;
    //prijde sem nejaka matice, aby bylo mozne mit jeden model pro jeden typ objektu, apk jen upravovat pozice a velikosti matici
    //pridat mu atribut na barvu?
    //transformace agregace ci kompozice uz zalezi jak chceme
    Transformation* transformation;
    glm::vec3 position;

public:
    DrawableObject(Model* m, ShaderProgram* sp);
    ~DrawableObject(); //kazdy objekt ma zatim VLASTNI MODEL
    int getId() const { return id; }
    void MoveTo(float x, float y, float z);
    void Resize(float x, float y, float z);
    void Rotate(float angle, float xA, float yA, float zA);

    void draw();
};
