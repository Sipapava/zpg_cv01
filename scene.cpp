#include "Scene.h"
#include <algorithm> 
#include "circleBuild.h"
#include "tree.h"
#include "vertexDef.h"
#include "bushes.h"
#include "sphere.h"
//remake create and add methods fro DO and Shaders

int Scene::nextId = 0;
Scene::Scene() {
    id = nextId++;
}

Scene::~Scene() {
    
    for (auto obj : drawableObjects) {
        delete obj;
    }
    drawableObjects.clear();

    
    for (auto sp : shaderPrograms) {
        delete sp;
    }
    shaderPrograms.clear();

    for (auto m : models) {
        delete m;
    }
    models.clear();
}

void Scene::addShaderProgram(ShaderProgram* sp) {
    shaderPrograms.push_back(sp);
}

void Scene::addModel(Model* m) {
    models.push_back(m);
}


DrawableObject* Scene::CreateDrawableObject(Model* m, ShaderProgram* sp) {
    return new DrawableObject(m, sp);
}

Model* Scene::CreateModel(const Vertex* vertices, size_t count,bool color,std::string type) {
    return new Model(vertices, count,color,type);
}

void Scene::addDrawableObject(DrawableObject* obj) {
    drawableObjects.push_back(obj);
}

void Scene::draw() {
    // iterace pres shadery?
    for (auto obj : drawableObjects) {
        obj->Update();
        obj->draw();
    }
}

bool Scene::prepareTestSceneCv03T1() {
    

    std::vector<Vertex> circle = buildCircle(0.1f, 30);
    

        
    Shader* shader = new Shader(vertex_shader_color, fragment_shader_color);
    ShaderProgram* shaderProgram = new ShaderProgram(shader);

    Model* model_kruh = new Model(circle.data(), circle.size(), true, "triangles");

    // vytvoøení modelu z dat
   // Model* model_krychle = new Model(c, sizeof(c) / sizeof(Vertex), true,"triangles");
    
    DrawableObject* obj_kruh1 = new DrawableObject(model_kruh, shaderProgram);
    obj_kruh1->MoveTo(0, 0.5, 0);

    DrawableObject* obj_kruh2 = new DrawableObject(model_kruh, shaderProgram);
    obj_kruh2->MoveTo(-0.5, 0, 0);

    DrawableObject* obj_kruh3 = new DrawableObject(model_kruh, shaderProgram);
    obj_kruh3->MoveTo(0.5, 0, 0);

    DrawableObject* obj_kruh4 = new DrawableObject(model_kruh, shaderProgram);
    obj_kruh4->MoveTo(0, -0.5, 0);

    this->addModel(model_kruh);
    this->addDrawableObject(obj_kruh1);
    this->addDrawableObject(obj_kruh2);
    this->addDrawableObject(obj_kruh3);
    this->addDrawableObject(obj_kruh4);

    return true;

}

bool Scene::prepareTestSceneCv03T2() {
    const Vertex simpleT[] = {

        { { -0.8f, -0.5f, 0, 1 }, { 1, 0, 0, 1 } }, // - èervená
        { { -0.8f,  -0.3f, 0, 1 }, { 1, 1, 0, 1 } }, // - žlutá
        { {  -0.3f,  -0.3f, 0, 1 }, { 0, 0, 1, 1 } }, //  - modrá

    };

    Shader* shader = new Shader(vertex_shader_color, fragment_shader_color);
    ShaderProgram* shaderProgram = new ShaderProgram(shader);
    Model* model_trojuhe = new Model(simpleT, sizeof(simpleT) / sizeof(Vertex), true, "triangles");
    DrawableObject* obj_trojuhe = new DrawableObject(model_trojuhe, shaderProgram);
    obj_trojuhe->SetRotateAnimation(glm::radians(1.0f), glm::vec3(0, 0, 1));

    this->addModel(model_trojuhe);
    this->addDrawableObject(obj_trojuhe);
    return true;
}

bool Scene::prepareTestSceneCv03T3() {
    // --- Vertex data ---
    const int treeSize = sizeof(tree) / sizeof(tree[0]);
    std::vector<Vertex> treeV = FromFloat(tree, treeSize);

    const int sphereSize = sizeof(sphere) / sizeof(sphere[0]);
    std::vector<Vertex> sphereV = FromFloat(sphere, sphereSize);

    const int bushSize = sizeof(bushes) / sizeof(bushes[0]);
    std::vector<Vertex> bushV = FromFloat(bushes, bushSize);

    // --- Shadery ---
    Shader* shaderColor = new Shader(vertex_shader_color, fragment_shader_color);
    ShaderProgram* shaderProgramColor = new ShaderProgram(shaderColor);
    addShaderProgram(shaderProgramColor);

    Shader* shaderBasic = new Shader(vertex_shader, fragment_shader);
    ShaderProgram* shaderProgramBasic = new ShaderProgram(shaderBasic);
    addShaderProgram(shaderProgramBasic);

    // --- Modely ---
    Model* sphereModel = new Model(sphereV.data(), sphereV.size(), true, "triangles");
    Model* treeModel = new Model(treeV.data(), treeV.size(), true, "triangles");
    Model* bushModel = new Model(bushV.data(), bushV.size(), true, "triangles");

    addModel(sphereModel);
    addModel(treeModel);
    addModel(bushModel);

    
    std::vector<glm::vec3> sunPositions = { {-0.8f, 0.8f, 0.0f}, {0.8f, 0.8f, 0.0f} };
    for (auto& pos : sunPositions) {
        DrawableObject* sun = CreateDrawableObject(sphereModel, shaderProgramColor);
        sun->Resize(0.1f, 0.1f, 0.1f);
        sun->MoveTo(pos.x, pos.y, pos.z); 
        sun->SetRotateAnimation(glm::radians(1.0f), glm::vec3(0, 0.5, 0.5));
        addDrawableObject(sun);
    }

    
    for (int i = 0; i < 8; ++i) {
        DrawableObject* treeObj = CreateDrawableObject(treeModel, shaderProgramColor);

        float x = -0.7f + i * 0.2f; 
        float y = -0.3f;            
        float z = 0.0f;             

        treeObj->Resize(0.1f, 0.1f, 0.1f);
        treeObj->MoveTo(x, y, z);
        addDrawableObject(treeObj);
    }

    
    for (int i = 0; i < 10; ++i) {
        DrawableObject* bushObj = CreateDrawableObject(bushModel, shaderProgramColor);

        float x = -0.9f + (i % 5) * 0.45f;      
        float y = -0.7f + (i / 5) * -0.2f;      
        float z = 0.0f;                          

        bushObj->Resize(0.3f, 0.3f, 0.3f);
        bushObj->MoveTo(x, y, z);
        addDrawableObject(bushObj);
    }




    
    return true;
    
}




