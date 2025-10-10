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

bool Scene::prepareTestSceneCv03T3() {
    // --- Vertex data ---
    const int treeSize = sizeof(tree) / sizeof(tree[0]);
    std::vector<Vertex> treeV = FromFloat(tree, treeSize);

    const int sphereSize = sizeof(sphere) / sizeof(sphere[0]);
    std::vector<Vertex> sphereV = FromFloat(sphere, sphereSize);

    const int bushSize = sizeof(bushes) / sizeof(bushes[0]);
    std::vector<Vertex> bushV = FromFloat(bushes, bushSize);

    // --- Shadery ---
    Camera* camera = new Camera();
    camera = camera;
    Shader* shaderColor = new Shader(vertex_shader_color, fragment_shader_color);
    ShaderProgram* shaderProgramColor = new ShaderProgram(shaderColor,camera);
    addShaderProgram(shaderProgramColor);

    Shader* shaderBasic = new Shader(vertex_shader, fragment_shader);
    ShaderProgram* shaderProgramBasic = new ShaderProgram(shaderBasic,camera);
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




