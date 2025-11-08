
#include "drawableObject.h"
#include <stdio.h>

int DrawableObject::nextId = 0;

DrawableObject::DrawableObject(Model* m, ShaderProgram* sp)
    : model(m), shaderProgram(sp) {
    complexTransformation* complexTrans = new complexTransformation();
    transformation = complexTrans;
    id = nextId++;
    if (model) {
        position = model->ComputeInitialCenter();
    }
    
   
    updateColor = false;

}

DrawableObject::~DrawableObject() {
    //delete model; zodpovednost prebrala scena
    delete transformation;

    for (auto& t : textures) {
        delete t;    // destruktor Texture se postará o glDeleteTextures
        t = nullptr;
    }
    textures.clear();
}

void DrawableObject::AddTexture(Texture* t) {
    textures.push_back(t);
};

void DrawableObject::SetRotateAnimation(float addAngle, const glm::vec3& axis) {

    transformation->Add(new RotationDynamic(0.0f, axis, addAngle));

};

void DrawableObject::SetRandomMoveAnimation(float speed, int maxSteps) {

    transformation->Add(new RandomTranslation(speed, maxSteps));

};




void DrawableObject::Update() {
    //prazdna

};

void DrawableObject::draw() {
    if (shaderProgram) { //must be if, cause some lights have models and shaderprograms set tu null
        bool x = shaderProgram->setShaderProgram(); // aktivuje shader

        
    shaderProgram->ProjectionApply();
    shaderProgram->LightApply();

    glm::mat4 I = glm::mat4(1.0f);
    glm::mat4 M = transformation->apply(I);
    int ready = shaderProgram->setUniform(M);

    if (!updateColor) {
        shaderProgram->setUniform4(this->color, "color");
        updateColor = true;
    }

    
     //  Bind textur
    for (auto t : textures) {
        if (!t) continue;
        t->ActiveTexture();
        t->BindTexture();

        // Uniform dostane slot podle typu
        shaderProgram->setUniformInt(t->GetSlot(), t->GetType().c_str()); //upravit to type asi
    }

    
    

    if (model && ready) { //pridat if na projection
        model->Draw(); // bindne VAO a vykreslí


    }
    shaderProgram->resetShaderProgram();
   }

}



void DrawableObject::MoveTo(float x, float y, float z) {
    glm::vec3 delta = glm::vec3(x, y, z);
    transformation->Add(new Translation(delta));

}

void DrawableObject::Resize(float x, float y, float z) {
    transformation->Add(new Scale(glm::vec3(x, y, z)));

}

void DrawableObject::Rotate(float angle, float xA, float yA, float zA) {
    transformation->Add(new Rotation(angle, glm::vec3(xA, yA, zA)));


}

void DrawableObject::setColor(const glm::vec4& color) {
    this->updateColor = false;
    this->color = color;
}


