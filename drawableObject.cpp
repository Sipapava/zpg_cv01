#include "drawableObject.h"
#include <stdio.h>

int DrawableObject::nextId = 0;

DrawableObject::DrawableObject(Model* m, ShaderProgram* sp)
    : model(m), shaderProgram(sp) {
    complexTransformation* complexTrans = new complexTransformation();
    transformation = complexTrans;
    id = nextId++;
    position = model->ComputeInitialCenter();
    
}

DrawableObject::~DrawableObject() {
    delete model;
    delete transformation;
}

void DrawableObject::draw() {
    if (shaderProgram) {
      bool x =  shaderProgram->setShaderProgram(); // aktivuje shader
    }
    //vytvorim ejednotkovou matici kterou vlozime od apply;
    //pak se zavola matice a  vykreslise, setUniform s matici volame tady

    glm::mat4 I = glm::mat4(1.0f);
    glm::mat4 M = transformation->apply(I);
    int d = shaderProgram->setUniform(M);

    if (model) {
        model->Draw(); // bindne VAO a vykresl�
       
    }
}

//void MoveTo(x,y,z); jen prida matici rotace do transformation
//void rotate je kolem vlastni osy
//void resize?
//musi mit delete na transoformation!

void DrawableObject::MoveTo(float x, float y, float z) {
    // spo��t�me posun relativn� k aktu�ln� pozici
    glm::vec3 delta = glm::vec3(x, y, z) - position;

    // vytvo��me translaci o rozd�l
    transformation->Add(new Translation(delta));

    // aktualizujeme st�ed objektu
    position = glm::vec3(x, y, z);
}

void DrawableObject::Resize(float x, float y, float z) {
    transformation->Add(new Scale(glm::vec3(x, y, z)));;
}

void DrawableObject::Rotate(float angle, float xA, float yA, float zA) {
    // krok 1: posunout st�ed objektu do po��tku
    transformation->Add(new Translation(-position));

    // krok 2: aplikovat rotaci kolem zadan� osy
    transformation->Add(new Rotation(angle, glm::vec3(xA, yA, zA)));

    // krok 3: posunout objekt zp�t na p�vodn� pozici
    transformation->Add(new Translation(+position));
}

