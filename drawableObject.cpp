
#include "drawableObject.h"
#include <stdio.h>

int DrawableObject::nextId = 1;

DrawableObject::DrawableObject(Model* m, ShaderProgram* sp,std::string type)
    : model(m), shaderProgram(sp) {
    complexTransformation* complexTrans = new complexTransformation();
    transformation = complexTrans;
    id = nextId++;
    if (model) {
        position = model->ComputeInitialCenter();
    }
    this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    this->type = type;
    material = new Material();

}

DrawableObject::~DrawableObject() {
    
    delete transformation;

    for (auto& t : textures) {
        delete t;    
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

void DrawableObject::moveOnBezier(glm::vec3 controlPoints[4], float speed) {
    transformation->Add(new Bezier(controlPoints, speed));
}

void DrawableObject::moveOnCustomeBezier(const std::vector<glm::vec3>& points, float speed) {
    transformation->Add(new BezierCustom(points, speed));
};

std::string DrawableObject::GetType() {
    return this->type;
}


void DrawableObject::Update() {
 
};

void DrawableObject::draw() {
    if (shaderProgram) { //must be if, cause some lights have models and shaderprograms set tu null
        bool x = shaderProgram->setShaderProgram(); 
        
        glStencilFunc(GL_ALWAYS, getId(), 0xFF);

    shaderProgram->ProjectionApply();
    shaderProgram->LightApply();

    glm::mat4 I = glm::mat4(1.0f);
    glm::mat4 M = transformation->apply(I);
    int ready = shaderProgram->setUniform(M);

    shaderProgram->setUniform4(this->color, "color");
    shaderProgram->materialApply(this->material);
        
     
    for (auto t : textures) {
        if (!t) continue;
        t->ActiveTexture();
        t->BindTexture();

        shaderProgram->setUniformInt(t->GetSlot(), t->GetType().c_str()); //do...update types
    }

    if (model && ready) { 
        model->Draw(); 
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

void DrawableObject::moveOnLine(float speed) {
    transformation->Add(new RandomLine(speed));
}

void DrawableObject::setCustomTransformation(const glm::mat4x4& matrix) {
    transformation->Add(new CostumTransformation(matrix));
}

//cancel this each object has individual color so shader Must do setUnifrm for eaach
void DrawableObject::setColor(const glm::vec4& color) {
    this->color = color;
}

void DrawableObject::setMaterial(Material *m) {
    this->material = m;
}



