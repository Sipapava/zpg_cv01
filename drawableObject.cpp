#include "drawableObject.h"

DrawableObject::DrawableObject(Model* m, ShaderProgram* sp)
    : model(m), shaderProgram(sp) {}

DrawableObject::~DrawableObject() {
   
}

void DrawableObject::draw() {
    if (shaderProgram) {
      bool x =  shaderProgram->setShaderProgram(); // aktivuje shader
    }
    if (model) {
        model->Draw(); // bindne VAO a vykreslí
    }
}
