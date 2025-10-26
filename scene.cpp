#include "Scene.h"
#include <algorithm> 
#include "circleBuild.h"
#include "tree.h"

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

    for (auto l : lights) {
        delete l;
    }
    lights.clear();
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

Light* Scene::CreateLight(const glm::vec3& position, const glm::vec4& colorSpecular, float intesnity, float shiness, const glm::vec4& colorDiffuse, float attenuation) {
    return new Light(position, colorSpecular, intesnity, shiness,colorDiffuse,attenuation);
}

void Scene::AddLight(Light* l) {
    lights.push_back(l);
}

void Scene::draw() {
    // Nejprve aktualizuj všechna svìtla (napø. dynamické transformace)
    for (auto light : lights) {
        if (light) {
            light->Update();
        }
    }

    // Poté aktualizuj a vykresli všechny kreslitelné objekty
    for (auto obj : drawableObjects) {
        if (obj) {
            obj->Update();
            obj->draw();
        }
    }
}


bool Scene::prepareTestSceneCv05T1() {


   
    return true;
}

bool Scene::prepareTestSceneCv05T2() {
    Shader* vr1 = new Shader();
    Shader* fr1 = new Shader();
    vr1->createShaderFromFile(GL_VERTEX_SHADER, "vertex_shader_ph.glsl");
    fr1->createShaderFromFile(GL_FRAGMENT_SHADER, "fragment_shader_blph.glsl");


    const int sphereSize = sizeof(sphere) / sizeof(sphere[0]);
    std::vector<Vertex> sphereV = FromFloat(sphere, sphereSize);



    this->camera = this->CreateCamera();

    
    Light* l = this->CreateLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0), 0.5f, 32, glm::vec4(0.385, 0.647, 0.812, 1.0), 2.5);
  
    ShaderProgram* shaderProgramBl = new ShaderProgram(vr1, fr1);
    
    addShaderProgram(shaderProgramBl);
   
   AddLight(l);
    camera->AddObserver(shaderProgramBl);
    l->AddObserver(shaderProgramBl);


  
    
    camera->UpdateMatrix();
    l->UpdateLightsShaderPro();
    




    Model* sphereModel = new Model(sphereV.data(), sphereV.size(), true, "triangles");


    addModel(sphereModel);

    DrawableObject* sun = CreateDrawableObject(sphereModel, shaderProgramBl);
    sun->Resize(0.3f, 0.3f, 0.3f);
    sun->SetRotateAnimation(glm::radians(1.0f), glm::vec3(0, 0.5, 0.5));
    addDrawableObject(sun);

    DrawableObject* earth = CreateDrawableObject(sphereModel, shaderProgramBl);
    earth->Resize(0.1f, 0.1f, 0.1f);
    earth->SetRotateAnimation(glm::radians(1.0f), glm::vec3(0, 0.5, 0.5));
    earth->MoveTo(1.0f, 0.0f, 0.0f);
    earth->SetRotateAnimation(glm::radians(1.0f), glm::vec3(0, 1, 0));
    addDrawableObject(earth);

    DrawableObject* moon = CreateDrawableObject(sphereModel, shaderProgramBl);
    moon->Resize(0.05f, 0.05f, 0.05f);
    moon->SetRotateAnimation(glm::radians(1.0f), glm::vec3(0, 0.5, 0.5));
    moon->MoveTo(0.3f, 0.0f, 0.0f);
    moon->SetRotateAnimation(glm::radians(1.0f), glm::vec3(0, 1, 0));
    moon->MoveTo(1.0f, 0.0f, 0.0f);
    moon->SetRotateAnimation(glm::radians(1.0f), glm::vec3(0, 1, 0));
    addDrawableObject(moon);
    
    return true;
}

bool Scene::prepareTestSceneCv05T3() {
    Shader* vr1 = new Shader();
    Shader* fr1 = new Shader();
    vr1->createShaderFromFile(GL_VERTEX_SHADER, "vertex_shader_con.glsl");
    fr1->createShaderFromFile(GL_FRAGMENT_SHADER, "fragment_shader_con.glsl");

    Shader* vr2 = new Shader();
    Shader* fr2 = new Shader();
    vr2->createShaderFromFile(GL_VERTEX_SHADER, "vertex_shader_lam.glsl");
    fr2->createShaderFromFile(GL_FRAGMENT_SHADER, "fragment_shader_lam.glsl");

    Shader* vr3 = new Shader();
    Shader* fr3 = new Shader();
    vr3->createShaderFromFile(GL_VERTEX_SHADER, "vertex_shader_ph.glsl");
    fr3->createShaderFromFile(GL_FRAGMENT_SHADER, "fragment_shader_ph.glsl");


    Shader* vr4 = new Shader();
    Shader* fr4 = new Shader();
    vr4->createShaderFromFile(GL_VERTEX_SHADER, "vertex_shader_ph.glsl");
    fr4->createShaderFromFile(GL_FRAGMENT_SHADER, "fragment_shader_blph.glsl");


    const int sphereSize = sizeof(sphere) / sizeof(sphere[0]);
    std::vector<Vertex> sphereV = FromFloat(sphere, sphereSize);



    this->camera = this->CreateCamera();


    Light* l = this->CreateLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0), 0.5f, 32, glm::vec4(0.385, 0.647, 0.812, 1.0), 0.001);
    ShaderProgram* shaderProgramCon = new ShaderProgram(vr1, fr1);
    ShaderProgram* shaderProgramAm = new ShaderProgram(vr2, fr2);
    ShaderProgram* shaderProgramBl = new ShaderProgram(vr3, fr3);
    ShaderProgram* shaderProgramBlPh = new ShaderProgram(vr4, fr4);
    addShaderProgram(shaderProgramCon);
    addShaderProgram(shaderProgramAm);
    addShaderProgram(shaderProgramBl);
    addShaderProgram(shaderProgramBlPh);
    AddLight(l);
    camera->AddObserver(shaderProgramCon);
    camera->AddObserver(shaderProgramAm);
    camera->AddObserver(shaderProgramBl);
    camera->AddObserver(shaderProgramBlPh);

   
   l->AddObserver(shaderProgramBl);
    l->AddObserver(shaderProgramBlPh);
    l->AddObserver(shaderProgramAm);
    camera->UpdateMatrix();
    l->UpdateLightsShaderPro();

    
   

    Model* sphereModel = new Model(sphereV.data(), sphereV.size(), true, "triangles");
    

    addModel(sphereModel);
    

    int i = 0;
    std::vector<glm::vec3> sunPositions = { {-0.5f, 0.0f, 0.0f}, {0.5f, 0.0f, 0.0f},{0.0f,0.5f,0.0f},{0.0f,-0.5f,0.0f} };
    for (auto& pos : sunPositions) {
        DrawableObject* sun = CreateDrawableObject(sphereModel, this->getShaderProgram(i));
        sun->Resize(0.1f, 0.1f, 0.1f);
        sun->MoveTo(pos.x, pos.y, pos.z); 
        //sun->SetRotateAnimation(glm::radians(1.0f), glm::vec3(0, 0.5, 0.5));
        addDrawableObject(sun);
        i++;
    }

    

    
    return true;
    
}

bool Scene::prepareTestSceneCv05T4(){
    const Vertex planeVertices[] = {
     {{-2.0f, -0.4f, 0.0f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}},
     {{ 2.0f, -0.4f, 0.0f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}},
     {{ 2.0f, -0.4f, 2.5f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}},

     {{ 2.0f, -0.4f, 2.5f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}},
     {{-2.0f, -0.4f, 2.5f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}},
     {{-2.0f, -0.4f, 0.0f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}}
    };

    const int treeSize = sizeof(tree) / sizeof(tree[0]);
    std::vector<Vertex> treeV = FromFloat(tree, treeSize);

    const int sphereSize = sizeof(sphere) / sizeof(sphere[0]);
    std::vector<Vertex> sphereV = FromFloat(sphere, sphereSize);

    const int bushSize = sizeof(bushes) / sizeof(bushes[0]);
    std::vector<Vertex> bushV = FromFloat(bushes, bushSize);
    Shader* vr = new Shader();
    Shader* fr = new Shader();
    vr->createShaderFromFile(GL_VERTEX_SHADER, "vertex_shader_ph.glsl");
    fr->createShaderFromFile(GL_FRAGMENT_SHADER, "fragment_shader_blph.glsl");
    this->camera = this->CreateCamera();

    
    Light* l1 = this->CreateLight(glm::vec3(0.0f, 0.0f, 0.0f),   
        glm::vec4(1.0, 1.0, 1.0, 1.0), 
        0.6f,                           
        32.0f,                          
        glm::vec4(0.8, 0.75, 0.3, 1.0), 
        5.0f);                        

    Light* l2 = this->CreateLight(glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec4(1.0, 1.0, 1.0, 1.0),
        0.6f,
        32.0f,
        glm::vec4(0.95, 0.55, 0.15, 1.0),
        5.f);

    Light* l3 = this->CreateLight(glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec4(1.0, 1.0, 1.0, 1.0),
        0.6f,
        32.0f,
        glm::vec4(1.0, 1.0, 0.7, 1.0),
        5.f);

    l1->MoveTo(-0.8f, 0.5f, 0.0);
    l2->MoveTo(0.8f, 0.4f, 0.0f);
    l3->MoveTo( 0.0f, 0.3f, 0.7f);
 
    ShaderProgram* shaderProgramColor = new ShaderProgram(vr, fr);
    addShaderProgram(shaderProgramColor);

    AddLight(l1);
    AddLight(l2);
    AddLight(l3);

    camera->AddObserver(shaderProgramColor);
    l1->AddObserver(shaderProgramColor);
    l2->AddObserver(shaderProgramColor);
    l3->AddObserver(shaderProgramColor);

   
    camera->UpdateMatrix();
    l1->UpdateLightsShaderPro();
    l2->UpdateLightsShaderPro();
    l3->UpdateLightsShaderPro();


    Model* planeModel = new Model(planeVertices, sizeof(planeVertices) / sizeof(Vertex), true, "triangles");
    addModel(planeModel);

    DrawableObject* bushPlane = CreateDrawableObject(planeModel, shaderProgramColor);
    bushPlane->Resize(10.0f, 10.0f, 10.0f);
    bushPlane->MoveTo(-2.0f, 4.0f, -2.0f);
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
        sun->SetRotateAnimation(glm::radians(1.0f), glm::vec3(0, 0.5, 0.5));
        sun->Resize(0.1f, 0.1f, 0.1f);
        sun->MoveTo(pos.x, pos.y, pos.z);
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
        float y = 0.05f;
        float z = 0.5f + row * 0.4f;

        bushObj->Resize(0.3f, 0.3f, 0.3f);
        bushObj->MoveTo(x, y, z);
        addDrawableObject(bushObj);
    }

    return true;
}


