#include "drawableObject.h"

int DrawableObject::nextId = 0;

DrawableObject::DrawableObject(Model* m, ShaderProgram* sp)
    : model(m), shaderProgram(sp) {
    id = nextId++;
}

DrawableObject::~DrawableObject() {
    delete model;
}

void DrawableObject::draw() {
    if (shaderProgram) {
      bool x =  shaderProgram->setShaderProgram(); // aktivuje shader
    }
    if (model) {
        model->Draw(); // bindne VAO a vykreslí
    }
}
