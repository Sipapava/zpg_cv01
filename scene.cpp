#include "Scene.h"
#include <algorithm> 
#include "circleBuild.h"
#include "tree.h"
#include "shaderDef.h"
#include "bushes.h"
#include "sphere.h"
//remake create and add methods for DrObj and Shaders

int Scene::nextId = 0;
Scene::Scene() {
    id = nextId++;
    camera = nullptr;
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

Camera* Scene::CreateCamera() {
    return new Camera(&this->shaderPrograms);
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
    


    return true;

}

bool Scene::prepareTestSceneCv03T2() {
    
    return true;
}

bool Scene::prepareTestSceneCv04T1() {
    const Vertex planeVertices[] = {
       
        {{ -2.0f, -0.4f, 0.0f,1.0f},{ 0.0f, 0.5f, 0.0f,1.0f}},  
        { {2.0f, -0.4f, 0.0f,1.0f},{ 0.0f, 0.5f, 0.0f,1.0f} },  
        { {2.0f, -0.4f, 2.5f,1.0f}, {0.0f, 0.5f, 0.0f,1.0f}},  
        {{-2.0f, -0.4f, 2.5f,1.0f},{ 0.0f, 0.5f, 0.0f,1.0f} }   
    };

    const int treeSize = sizeof(tree) / sizeof(tree[0]);
    std::vector<Vertex> treeV = FromFloat(tree, treeSize);

    const int sphereSize = sizeof(sphere) / sizeof(sphere[0]);
    std::vector<Vertex> sphereV = FromFloat(sphere, sphereSize);

    const int bushSize = sizeof(bushes) / sizeof(bushes[0]);
    std::vector<Vertex> bushV = FromFloat(bushes, bushSize);

    
    this->camera = this->CreateCamera();
    Shader* shaderColor = new Shader(vertex_shader_color, fragment_shader_color);
    ShaderProgram* shaderProgramColor = new ShaderProgram(shaderColor,this->camera);
    addShaderProgram(shaderProgramColor);

    Shader* shaderBasic = new Shader(vertex_shader, fragment_shader);
    ShaderProgram* shaderProgramBasic = new ShaderProgram(shaderBasic,this->camera);
    addShaderProgram(shaderProgramBasic);

    
    Model* planeModel = new Model(planeVertices, sizeof(planeVertices) / sizeof(Vertex), true, "triangles");
    addModel(planeModel);

    DrawableObject* bushPlane = CreateDrawableObject(planeModel, shaderProgramColor);
    bushPlane->Resize(10.0f, 10.0f, 10.0f);
    bushPlane->MoveTo(0.0f, -0.42f, 6.25f); 
    addDrawableObject(bushPlane);

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

    
    int totalTrees = 50;
    int totalBushes = 50;

    //  Stromy
    int treeRows = 10;
    int treeCols = 5;
    for (int i = 0; i < totalTrees; ++i) {
        DrawableObject* treeObj = CreateDrawableObject(treeModel, shaderProgramColor);

        int row = i / treeCols;
        int col = i % treeCols;

        float x = -1.0f + col * 0.5f; 
        float y = 0.0f;              
        float z = -1.0f + row * 0.5f; 

        treeObj->Resize(0.1f, 0.1f, 0.1f);
        treeObj->MoveTo(x, y, z);
        addDrawableObject(treeObj);
    }

    // Keøe
    int bushRows = 10;
    int bushCols = 5;
    for (int i = 0; i < totalBushes; ++i) {
        DrawableObject* bushObj = CreateDrawableObject(bushModel, shaderProgramColor);

        int row = i / bushCols;
        int col = i % bushCols;

        float x = -1.0f + col * 0.4f; 
        float y = -0.35f;               
        float z = 0.5f + row * 0.4f;  

        bushObj->Resize(0.3f, 0.3f, 0.3f);
        bushObj->MoveTo(x, y, z);
        addDrawableObject(bushObj);
    }
    
    return true;
    
}




