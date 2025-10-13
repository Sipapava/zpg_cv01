#include "drawableObject.h"
#include <stdio.h>

int DrawableObject::nextId = 0;

DrawableObject::DrawableObject(Model* m, ShaderProgram* sp)
    : model(m), shaderProgram(sp) {
    complexTransformation* complexTrans = new complexTransformation();
    transformation = complexTrans;
    id = nextId++;
    position = model->ComputeInitialCenter();
    rotation[0] = 0; rotation[1] = 0; rotation[2] = 0;
    rotationAxis = { 0,0,0 };
    
}

DrawableObject::~DrawableObject() {
    //delete model; zodpovednost prebrala scena
    delete transformation;
}

void DrawableObject::SetRotateAnimation(float addAngle, const glm::vec3& axis) {
    transformation->Add(new Translation(-position));
    transformation->Add(new RotationDynamic(0.0f, axis, addAngle));
    transformation->Add(new Translation(+position));
};



void DrawableObject::Update() {
    //prazdna

};

void DrawableObject::draw() {
    if (shaderProgram) {
      bool x =  shaderProgram->setShaderProgram(); // aktivuje shader
    }
    
    shaderProgram->ProjectionApply();

    glm::mat4 I = glm::mat4(1.0f);
    glm::mat4 M = transformation->apply(I);
    int ready = shaderProgram->setUniform(M);

    if (model && ready) { //pridat if na projection
        model->Draw(); // bindne VAO a vykreslí
       
    }
}



void DrawableObject::MoveTo(float x, float y, float z) {
    
    glm::vec3 delta = glm::vec3(x, y, z) - position;

    transformation->Add(new Translation(delta));


    position = glm::vec3(x, y, z);
}

void DrawableObject::Resize(float x, float y, float z) {
    
    transformation->Add(new Translation(-position));
    transformation->Add(new Scale(glm::vec3(x, y, z)));
    transformation->Add(new Translation(position));
}

void DrawableObject::Rotate(float angle, float xA, float yA, float zA) {
    
    transformation->Add(new Translation(-position));

    
    transformation->Add(new Rotation(angle, glm::vec3(xA, yA, zA)));

   
    transformation->Add(new Translation(+position));
}

