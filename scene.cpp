#include "Scene.h"
#include <algorithm> 
#include "tree.h"

#include "bushes.h"
#include "sphere.h"
//remake create and add methods for DrObj and Shaders

int Scene::nextId = 0;
Scene::Scene() {
    id = nextId++;
    camera = nullptr;
    srand(static_cast<unsigned int>(time(nullptr)));
}

Scene::~Scene() {
 
    
    for (auto& obj : drawableObjects) {
        if (obj) {
        
        delete obj;
        obj = nullptr;
        }
    }
    drawableObjects.clear();

    lights.clear();


    for (auto& sp : shaderPrograms) {
      
        delete sp;
        sp = nullptr;
    }
    shaderPrograms.clear();

  
    for (auto& m : models) {
        
        delete m;
        m = nullptr;
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

std::vector<Vertex> Scene::LoadModelFromObjectFile(const char* path) {
    Assimp::Importer importer;
    std::vector<Vertex> vertices;
    
    const aiScene* scene = importer.ReadFile(path,
        aiProcess_Triangulate |
        aiProcess_FlipUVs |
        aiProcess_GenNormals);

    if (!scene || !scene->HasMeshes()) {
        std::cerr << "Assimp error: " << importer.GetErrorString() << std::endl;
        return vertices;
    }

    

    for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
        aiMesh* mesh = scene->mMeshes[m];

        for (unsigned int f = 0; f < mesh->mNumFaces; ++f) {
            aiFace& face = mesh->mFaces[f];
          
            for (unsigned int i = 0; i < face.mNumIndices; ++i) {
                unsigned int idx = face.mIndices[i];
                Vertex v;
                v.pos = glm::vec4(
                    mesh->mVertices[idx].x,
                    mesh->mVertices[idx].y,
                    mesh->mVertices[idx].z,
                    1.0f
                );

                if (mesh->HasNormals()) {
                    v.color = glm::vec4(
                        mesh->mNormals[idx].x,
                        mesh->mNormals[idx].y,
                        mesh->mNormals[idx].z,
                        1.0f
                    );
                }
                else {
                    v.color = glm::vec4(0, 0, 0, 0);
                }

                vertices.push_back(v);
            }
        }
    }

  
    return vertices;

}

std::vector<Vertex> Scene::FromFloat(const float* data, size_t size) {
    std::vector<Vertex> vertices;

    if (size % 6 != 0) {
        //throw std::runtime_error("Data size is not multiple of 6!");
    }

    for (size_t i = 0; i < size; i += 6) {
        Vertex v;
        v.pos = glm::vec4(data[i], data[i + 1], data[i + 2], 1.0f);
        v.color = glm::vec4(data[i + 3], data[i + 4], data[i + 5], 1.0f);
        vertices.push_back(v);
    }

    return vertices;
}


Camera* Scene::CreateCamera() {
    return new Camera(&this->shaderPrograms);
}
void Scene::addDrawableObject(DrawableObject* obj) {
    drawableObjects.push_back(obj);
}

void Scene::addDrawableObject(Light* lightObj) {
    drawableObjects.push_back(lightObj);  // vlastnictví pamìti
    if (std::find(lights.begin(), lights.end(), lightObj) == lights.end()) {
        lights.push_back(lightObj);       // nevlastní ukazatel
    }
}

/*
Light* Scene::CreateLight(const glm::vec3& position, const glm::vec4& colorSpecular, float intesnity, float shiness, const glm::vec4& colorDiffuse, float attenuation, const glm::vec4& ambientColor) {
    return new Light(position, colorSpecular, intesnity, shiness,colorDiffuse,attenuation,ambientColor);
}
*/


void Scene::draw() {
    
    
    for (auto light : lights) {
        if (light) {
            light->Update();
        }
    }
    
 
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
    /*
    Shader* vr1 = new Shader();
    Shader* fr1 = new Shader();
    vr1->createShaderFromFile(GL_VERTEX_SHADER, "vertex_shader_ph.glsl");
    fr1->createShaderFromFile(GL_FRAGMENT_SHADER, "fragment_shader_blph.glsl");


    const int sphereSize = sizeof(sphere) / sizeof(sphere[0]);
    std::vector<Vertex> sphereV = FromFloat(sphere, sphereSize);



    this->camera = this->CreateCamera();

    
    Light* l = this->CreateLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0), 0.5f, 32, glm::vec4(0.385, 0.647, 0.812, 1.0), 2.5, glm::vec4(0.1, 0.1, 0.1, 1.0));
  
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
    */
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

   
   ambientLight* a = new ambientLight(  glm::vec4(0.1, 0.1, 0.1, 1.0));
    
   glm::vec3 lightDirection = glm::vec3(0.0f, -1.0f, 0.0f);

  
   glm::vec4 specularColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); 
   glm::vec4 diffuseColor = glm::vec4(0.385, 0.647, 0.812, 1.0); 

   
   float intensity = 1.0f;
   float shininess = 32.0f;

   directLight* l =  new directLight(lightDirection, specularColor, diffuseColor, intensity, shininess);

    ShaderProgram* shaderProgramCon = new ShaderProgram(vr1, fr1);
    ShaderProgram* shaderProgramAm = new ShaderProgram(vr2, fr2);
    ShaderProgram* shaderProgramBl = new ShaderProgram(vr3, fr3);
   ShaderProgram* shaderProgramBlPh = new ShaderProgram(vr4, fr4);
    addShaderProgram(shaderProgramCon);
    addShaderProgram(shaderProgramAm);
    addShaderProgram(shaderProgramBl);
   addShaderProgram(shaderProgramBlPh);
    addDrawableObject(a);
    addDrawableObject(l);
    camera->AddObserver(shaderProgramCon);
    camera->AddObserver(shaderProgramAm);
    camera->AddObserver(shaderProgramBl);
    camera->AddObserver(shaderProgramBlPh);

   
   l->AddObserver(shaderProgramBl);
    l->AddObserver(shaderProgramBlPh);
    l->AddObserver(shaderProgramAm);
  
    a->AddObserver(shaderProgramBlPh);
   a->AddObserver(shaderProgramBl);
    camera->UpdateMatrix();
    l->UpdateLightsShaderPro();
    a->UpdateLightsShaderPro();

    
   

    Model* sphereModel = new Model(sphereV.data(), sphereV.size(), true, "triangles");
    std::vector<Vertex> form = this->LoadModelFromObjectFile("formula1.obj");
    Model* formula = new Model(form.data(), form.size(), true, "triangles");

    addModel(sphereModel);
    addModel(formula);
    

    int i = 0;
     
    std::vector<glm::vec3> sunPositions = { {-0.5f, 0.0f, 0.0f}, {0.5f, 0.0f, 0.0f},{0.0f,0.5f,0.0f},{0.0f,-0.5f,0.0f} };
    for (auto& pos : sunPositions) {
        DrawableObject* sun = CreateDrawableObject(formula, this->getShaderProgram(i));
        if (i == 0) {
            sun->setColor(glm::vec4(0.385, 0.647, 0.222, 1.0));
        }
        sun->Resize(0.01f, 0.01f, 0.01f);
        sun->MoveTo(pos.x, pos.y, pos.z);
        sun->SetRandomMoveAnimation(0.001f, 100);
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

    ShaderProgram* shaderProgramColor = new ShaderProgram(vr, fr);
    addShaderProgram(shaderProgramColor);


    Shader* vr2 = new Shader();
    Shader* fr2 = new Shader();
    vr2->createShaderFromFile(GL_VERTEX_SHADER, "vertex_shader_con.glsl");
    fr2->createShaderFromFile(GL_FRAGMENT_SHADER, "fragment_shader_con.glsl");
    ShaderProgram* shaderProgramBug = new ShaderProgram(vr2, fr2);
   
    addShaderProgram(shaderProgramBug);
  
    Model* sphereModel = new Model(sphereV.data(), sphereV.size(), true, "triangles");

    
    Model* treeModel = new Model(treeV.data(), treeV.size(), true, "triangles");

   
    Model* bushModel = new Model(bushV.data(), bushV.size(), true, "triangles");

    
    pointLight* l1 = new pointLight(sphereModel,shaderProgramBug,glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec4(1.0, 1.0, 1.0, 1.0),
        glm::vec4(0.8, 0.75, 0.3, 1.0),
        0.6f,
        32.0f,
        5.0f);

  
    pointLight* l2 = new pointLight(sphereModel, shaderProgramBug,glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec4(1.0, 1.0, 1.0, 1.0),
        glm::vec4(0.95, 0.55, 0.15, 1.0),
        0.6f,
        32.0f,
        5.0f);

    

    ambientLight* a = new ambientLight( glm::vec4(0.1, 0.1, 0.1, 1.0));


    reflectorLight *newReflector = new reflectorLight(
        glm::vec3(0.0f, 0.5f, -2.0f),               
        glm::vec3(0.0f, 0.0f, 0.0f),                   
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),  
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 
        1.0f,                   
        32.0f,                
        0.1f,                
        0.1f                   
    );


  
    l1->Resize(0.01f, 0.01f, 0.01f);
    l1->MoveTo(1.2f, 0.9f, 3.0f);
    l1->SetRandomMoveAnimation(0.001f, 1000);
    l2->Resize(0.01f, 0.01f, 0.01f);
    l2->MoveTo(0.7f, 0.5f, 0.0f);
    l2->SetRandomMoveAnimation(0.001f, 300);
  
   
 
    l1->setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
    l2->setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));


    
   
    camera->AddObserver(shaderProgramColor);
    camera->AddObserver(shaderProgramBug);
    camera->AddObserver(newReflector);
    l1->AddObserver(shaderProgramColor);
    l2->AddObserver(shaderProgramColor);
    a->AddObserver(shaderProgramColor);
   newReflector->AddObserver(shaderProgramColor);

   l1->AddObserver(shaderProgramBug);
   l2->AddObserver(shaderProgramBug);
   a->AddObserver(shaderProgramBug);
   newReflector->AddObserver(shaderProgramBug);


    

   
    camera->UpdateMatrix();
    l1->UpdateLightsShaderPro();
    l2->UpdateLightsShaderPro();
    a->UpdateLightsShaderPro();
   newReflector->UpdateLightsShaderPro();
  


    Model* planeModel = new Model(planeVertices, sizeof(planeVertices) / sizeof(Vertex), true, "triangles");
    addModel(planeModel);

    DrawableObject* bushPlane = CreateDrawableObject(planeModel, shaderProgramColor);
    bushPlane->Resize(10.0f, 10.0f, 10.0f);
    bushPlane->MoveTo(-2.0f, 4.0f, -2.0f);
    addDrawableObject(bushPlane);

    addDrawableObject(l1);
    addDrawableObject(l2);
    addDrawableObject(a);
    addDrawableObject(newReflector);

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
    
    // 
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


