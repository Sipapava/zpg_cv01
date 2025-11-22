
#define MINIAUDIO_IMPLEMENTATION
#include "Scene.h"
#include <algorithm> 
#include "tree.h"
#include "skycube.h"
#include "bushes.h"
#include "sphere.h"

//remake create and add methods for DrObj and Shaders

int Scene::nextId = 0;
Scene::Scene(ModelManager* mM) {
    id = nextId++;
    camera = nullptr;
    srand(static_cast<unsigned int>(time(nullptr)));
    ma_engine_init(NULL, &engine);
    modelManager = mM;
}

Scene::~Scene() {
    ma_engine_uninit(&engine);
    
    for (auto& obj : drawableObjects) {
        if (obj) {
        
        delete obj;
        obj = nullptr;
        }
    }
    drawableObjects.clear();

    for (auto& m : materials) {
        if (m) {

            delete m;
            m = nullptr;
        }
    }
    materials.clear();

    lights.clear();


    for (auto& sp : shaderPrograms) {
      
        delete sp;
        sp = nullptr;
    }
    shaderPrograms.clear();

 

}

void Scene::addShaderProgram(ShaderProgram* sp) {
    shaderPrograms.push_back(sp);
}




DrawableObject* Scene::CreateDrawableObject(Model* m, ShaderProgram* sp, std::string type) {
    return new DrawableObject(m, sp,type);
}



bool Scene::DeleteObject(int id) {
    auto oldSize = drawableObjects.size();

    for (auto it = drawableObjects.begin(); it != drawableObjects.end(); ) {
        DrawableObject* obj = *it;

        if (obj->getId() == id && obj->GetType() != "plane") {

            if (obj->GetType() == "simplePlane") {
                return true;
            }

            if (obj->GetType() == "zlobr") {
                ma_engine_play_sound(&this->engine, "hurt.mp3", NULL);
            }
            if (obj->GetType() == "cat") {
                ma_engine_play_sound(&this->engine, "cat.wav", NULL);
            }
            else {
                ma_engine_play_sound(&this->engine, "hit.mp3", NULL);
            }

            delete obj;
            it = drawableObjects.erase(it);
        }
        else {
            ++it;
        }
    }

    return drawableObjects.size() != oldSize;
}




bool Scene::BuildObject(float x, float y, float z) {
  

    Model* treeModel = modelManager->GetModelByName("tree");

    ShaderProgram* shaderProgramColor = shaderPrograms[0];

   
    DrawableObject* treeObj = CreateDrawableObject(treeModel, shaderProgramColor, "normal");
    if (!treeObj) {
   
        return false;
    }

  
    treeObj->setColor(glm::vec4(0.2f, 0.5f, 0.2f, 1.0f));

 
    Texture* t = new Texture();
    treeObj->AddTexture(t);


    treeObj->Resize(0.1f, 0.1f, 0.1f);

 
    treeObj->MoveTo(x, y , z);


    addDrawableObject(treeObj);

    
    
    ma_engine_play_sound(&engine, "plantSound.mp3", NULL);

    return true;
}



std::vector<Vertex> Scene::LoadModelFromObjectFile(const char* path) {
    Assimp::Importer importer;
    std::vector<Vertex> vertices;

    const aiScene* scene = importer.ReadFile(path,
        aiProcess_Triangulate  
    );

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
                    v.normal = glm::vec4(
                        mesh->mNormals[idx].x,
                        mesh->mNormals[idx].y,
                        mesh->mNormals[idx].z,
                        1.0f
                    );
                }
                else {
                    v.normal = glm::vec4(0, 0, 0, 0);
                }

                
                if (mesh->HasTextureCoords(0)) {
                    aiVector3D tex = mesh->mTextureCoords[0][idx];
                    v.texture = glm::vec2(tex.x, tex.y);
                }
                else {
                    v.texture = glm::vec2(0.0f, 0.0f);
                }

                vertices.push_back(v);
            }
        }
    }

    return vertices;
}

std::vector<Vertex> Scene::FromFloat(const float* data, size_t size, bool hasTexture, bool hasNormal) {
    std::vector<Vertex> vertices;

    // 3 (pos) + 3 (normal) + 2 (tex)
    size_t stride = 3 + (hasNormal ? 3 : 0) + (hasTexture ? 2 : 0);

    if (size % stride != 0) {
        std::cerr << " FromFloat: Data size (" << size
            << ") is not a multiple of stride (" << stride << ")!\n";
    }

    for (size_t i = 0; i < size; i += stride) {
        Vertex v;

        v.pos = glm::vec4(data[i], data[i + 1], data[i + 2], 1.0f);
        size_t offset = 3;

        if (hasNormal) {
            v.normal = glm::vec4(data[i + offset], data[i + offset + 1], data[i + offset + 2], 1.0f);
            offset += 3;
        }
        else {
            v.normal = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
        }

        if (hasTexture) {
            v.texture = glm::vec2(data[i + offset], data[i + offset + 1]);
            offset += 2;
        }
        else {
            v.texture = glm::vec2(1.0f);
        }

        vertices.push_back(v);
    }

    return vertices;
}




Camera* Scene::CreateCamera() {
    return new Camera();
}
void Scene::addDrawableObject(DrawableObject* obj) {
    drawableObjects.push_back(obj);
}

void Scene::addDrawableObject(Light* lightObj) {
    drawableObjects.push_back(lightObj);  
    if (std::find(lights.begin(), lights.end(), lightObj) == lights.end()) {
        lights.push_back(lightObj);      
    }
}

Material* Scene::CreateMaterial(const glm::vec4& ambient,
    const glm::vec4& diffuse,
    const glm::vec4& specular,
    const float shin)
{
    Material* m = new Material(ambient, diffuse, specular, shin);
    materials.push_back(m);
    return m;
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

    Shader* vr = new Shader();
    Shader* fr = new Shader();
    this->camera = this->CreateCamera();
    vr->createShaderFromFile(GL_VERTEX_SHADER, "vertex_shader_ph.glsl");
    fr->createShaderFromFile(GL_FRAGMENT_SHADER, "fragment_shader_blph.glsl");

    ShaderProgram* shaderProgramColor = new ShaderProgram(vr, fr);
    addShaderProgram(shaderProgramColor);

    Model* sphereModel = modelManager->GetModelByName("sphere");
    DrawableObject* sun = CreateDrawableObject(sphereModel, shaderProgramColor, "normal");
    Texture* t = new Texture();
    sun->AddTexture(t);
    sun->SetRotateAnimation(glm::radians(1.0f), glm::vec3(0, 0.5, 0.5));
    sun->Resize(0.1f, 0.1f, 0.1f);

    glm::mat4 custom = glm::mat4(1.0f);
    custom[3][3] = 20.0f;


    sun->setCustomTransformation(custom);

    sun->setColor(glm::vec4(0.9f, 0.1f, 0.5f, 1.0f));
    glm::vec3 lightDirection = glm::vec3(0.0f, -1.0f, 0.0f);


    glm::vec4 specularColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec4 diffuseColor = glm::vec4(0.385, 0.647, 0.812, 1.0);



    float intensity = 1.0f;
    float shininess = 32.0f;

    directLight* l = new directLight(lightDirection, specularColor, diffuseColor, intensity, shininess);



    ambientLight* a = new ambientLight(glm::vec4(0.1, 0.1, 0.1, 1.0));
    camera->AddObserver(shaderProgramColor);

    a->AddObserver(shaderProgramColor);
    l->AddObserver(shaderProgramColor);
    addDrawableObject(sun);
    camera->UpdateMatrix();
    addDrawableObject(a);
    addDrawableObject(l);

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


   
    //-----------------------------------------------------------------------------------
    std::vector<std::string> faces = {
    "skybox/posx.jpg",
    "skybox/negx.jpg",
    "skybox/posy.jpg",
    "skybox/negy.jpg",
    "skybox/posz.jpg",
    "skybox/negz.jpg"
    };

    Texture* skyboxTexture = new Texture(faces, "skybox");
    
    Model* skyModel = modelManager->GetModelByName("skyCube");


    Shader* vrS = new Shader();
    Shader* frS = new Shader();
    vrS->createShaderFromFile(GL_VERTEX_SHADER, "vertex_shader_cube.glsl");
    frS->createShaderFromFile(GL_FRAGMENT_SHADER, "fragment_shader_cube.glsl");
   
   
    
   

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
   ShaderProgram* shaderProgramSky = new ShaderProgram(vrS, frS);
    addShaderProgram(shaderProgramCon);
    addShaderProgram(shaderProgramAm);
    addShaderProgram(shaderProgramBl);
   addShaderProgram(shaderProgramBlPh);
   addShaderProgram(shaderProgramSky);
    addDrawableObject(a);
    addDrawableObject(l);
    camera->AddObserver(shaderProgramCon);
    camera->AddObserver(shaderProgramAm);
    camera->AddObserver(shaderProgramBl);
    camera->AddObserver(shaderProgramBlPh);
    camera->AddObserver(shaderProgramSky);

   
   l->AddObserver(shaderProgramBl);
    l->AddObserver(shaderProgramBlPh);
    l->AddObserver(shaderProgramAm);
  
    a->AddObserver(shaderProgramBlPh);
   a->AddObserver(shaderProgramBl);
    camera->UpdateMatrix();
    l->UpdateLightsShaderPro();
    a->UpdateLightsShaderPro();

  

    Model* sphereModel = modelManager->GetModelByName("sphere");
    std::vector<Vertex> form = this->LoadModelFromObjectFile("formula1.obj");
    Model* formula = modelManager->GetModelByName("formule");
    //Model* skyModel = new Model(cubeV.data(), cubeV.size(), "triangles", "cube");

    
    

    int i = 0;
    std::vector<Texture*> vv;
    Texture* t1 = new Texture("wooden_fence.png", "texture_test");
    Texture* t2 = new Texture("wooden_fence.png", "texture_test");
    Texture* t3 = new Texture("wooden_fence.png", "texture_test");
    Texture* t4 = new Texture("wooden_fence.png", "texture_test");
    vv.push_back(t1);
    vv.push_back(t2);
    vv.push_back(t3);
    vv.push_back(t4);
    
    drawableSky* sky = new drawableSky(skyModel, shaderProgramSky);
    sky->AddTexture(skyboxTexture);
    addDrawableObject(sky);
     
    std::vector<glm::vec3> sunPositions = { {-0.5f, 0.0f, 0.0f}, {0.5f, 0.0f, 0.0f},{0.0f,0.5f,0.0f},{0.0f,-0.5f,0.0f} };
    for (auto& pos : sunPositions) {
        DrawableObject* sun = CreateDrawableObject(formula, this->getShaderProgram(i),"normal");
        
        sun->Resize(0.01f, 0.01f, 0.01f);
        sun->MoveTo(pos.x, pos.y, pos.z);
        sun->SetRandomMoveAnimation(0.001f, 100);
        //sun->SetRotateAnimation(glm::radians(1.0f), glm::vec3(0, 0.5, 0.5));
        sun->AddTexture(vv[i]);
        addDrawableObject(sun);
        i++;
    }

    

    
    return true;
    
}

bool Scene::prepareTestSceneCv05T4(){
    
    
    
    Shader* vr = new Shader();
    Shader* fr = new Shader();
    vr->createShaderFromFile(GL_VERTEX_SHADER, "vertex_shader_ph.glsl");
    fr->createShaderFromFile(GL_FRAGMENT_SHADER, "fragment_shader_blph.glsl");
    
    this->camera = this->CreateCamera();

    ShaderProgram* shaderProgramColor = new ShaderProgram(vr, fr);
    addShaderProgram(shaderProgramColor);

    Model* sphereModel = modelManager->GetModelByName("sphere");


    Model* treeModel = modelManager->GetModelByName("tree");


    Model* bushModel = modelManager->GetModelByName("bush");
    Shader* vr2 = new Shader();
    Shader* fr2 = new Shader();
    vr2->createShaderFromFile(GL_VERTEX_SHADER, "vertex_shader_con.glsl");
    fr2->createShaderFromFile(GL_FRAGMENT_SHADER, "fragment_shader_con.glsl");
    ShaderProgram* shaderProgramBug = new ShaderProgram(vr2, fr2);
   
    addShaderProgram(shaderProgramBug);
  
    
    pointLight* l1 = new pointLight(sphereModel,shaderProgramBug,glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec4(1.0, 1.0, 1.0, 1.0),
        glm::vec4(0.8, 0.75, 0.3, 1.0),
        0.6f,
        32.0f,
        5.0f);

    Texture* t1 = new Texture();
    l1->AddTexture(t1);

  
    pointLight* l2 = new pointLight(sphereModel, shaderProgramBug,glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec4(1.0, 1.0, 1.0, 1.0),
        glm::vec4(0.95, 0.55, 0.15, 1.0),
        0.6f,
        32.0f,
        5.0f);
    Texture* t2 = new Texture();
    l2->AddTexture(t2);
    

    ambientLight* a = new ambientLight( glm::vec4(0.1, 0.1, 0.1, 1.0));


    reflectorLightCamera *newReflector = new reflectorLightCamera(
        glm::vec3(0.0f, 0.5f, -2.0f),               
        glm::vec3(0.0f, 0.0f, 0.0f),                   
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),  
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 
        1.0f,                   
        32.0f,                
        0.1f,                
        1.0f                   
    );

    Texture* skyboxTexture = new Texture("sunset.jpg", "skyTexture");
   
    Model* skyModel = modelManager->GetModelByName("skyDom");


    Shader* vrS = new Shader();
    Shader* frS = new Shader();
    vrS->createShaderFromFile(GL_VERTEX_SHADER, "vertex_shader_skydom.glsl");
    frS->createShaderFromFile(GL_FRAGMENT_SHADER, "fragment_shader_skydom.glsl");
    ShaderProgram* shaderProgramSky = new ShaderProgram(vrS, frS);
    addShaderProgram(shaderProgramSky);

    drawableSky* sky = new drawableSky(skyModel, shaderProgramSky);
    sky->AddTexture(skyboxTexture);
    addDrawableObject(sky);


  
    l1->Resize(0.01f, 0.01f, 0.01f);
    l1->MoveTo(1.2f, 0.9f, 3.0f);
    l1->SetRandomMoveAnimation(0.001f, 1000);
    l2->Resize(0.01f, 0.01f, 0.01f);
    l2->MoveTo(0.7f, 0.5f, 0.0f);
    l2->SetRandomMoveAnimation(0.001f, 300);
  
   
 
    l1->setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
    l2->setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));



    Shader* vC = new Shader();
    Shader* frC = new Shader();
    vC->createShaderFromFile(GL_VERTEX_SHADER, "vertex_shader_con.glsl");
    frC->createShaderFromFile(GL_FRAGMENT_SHADER, "fragment_shader_con.glsl");
    ShaderProgram* shaderProgramCon = new ShaderProgram(vC, frC);
    addShaderProgram(shaderProgramCon);

   
    camera->AddObserver(shaderProgramColor);
    camera->AddObserver(shaderProgramBug);
    camera->AddObserver(newReflector);
    camera->AddObserver(shaderProgramSky);
    camera->AddObserver(shaderProgramCon);
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
  


    Model* planeModel = modelManager->GetModelByName("plane");
 

    DrawableObject* bushPlane = CreateDrawableObject(planeModel, shaderProgramColor,"plane");
   
   Texture* t6 = new Texture("grass.jpg", "texture_test");
   bushPlane->AddTexture(t6);

    bushPlane->Resize(10.0f, 10.0f, 10.0f);
    bushPlane->MoveTo(-2.0f, 4.0f, -2.0f);
    addDrawableObject(bushPlane);

    
    Model* shrekM = modelManager->GetModelByName("shrek");

   
    Model* fionaM = modelManager->GetModelByName("fiona");

    Texture* shrekT = new Texture("shrek.png", "texture_test");
   
    Texture* fionaT = new Texture("fiona.png", "texture_test");


    Material* shrekMat = this->CreateMaterial(
        glm::vec4(0.1f, 0.1f, 0.1f, 1.0f),   // ambient
        glm::vec4(0.8f, 0.8f, 0.8f, 1.0f),   // diffuseh
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),  // specular
        5.0f    // shiness
    );

    DrawableObject* shrekD = CreateDrawableObject(shrekM, shaderProgramColor,"zlobr");
    shrekD->Resize(0.2f, 0.2f, 0.2f);
    shrekD->MoveTo( -1.5f, -0.002f, 0.0f );
    shrekD->setMaterial(shrekMat);
    
    DrawableObject* fionaD = CreateDrawableObject(fionaM, shaderProgramColor,"zlobr");
    fionaD->Rotate(glm::radians(180.0f), 0, 1, 0);
    fionaD->Resize(0.2f, 0.2f, 0.2f);
    fionaD->MoveTo(-1.5f, -0.002f, 0.2f);


    shrekD->AddTexture(shrekT);
    fionaD->AddTexture(fionaT);

    addDrawableObject(shrekD);
    addDrawableObject(fionaD);
    


    int totalTrees = 50;
    int totalBushes = 50;

   
    int treeRows = 10;
    int treeCols = 5;
    

   

    
    std::vector<glm::vec3> sunPositions = { {-0.8f, 0.8f, 0.0f}, {0.8f, 0.8f, 0.0f} };
    for (auto& pos : sunPositions) {
        DrawableObject* sun = CreateDrawableObject(sphereModel, shaderProgramColor,"normal");
        sun->setColor(glm::vec4(1.0f, 0.87f, 0.13f, 1.0f));
        Texture* t = new Texture();
        sun->AddTexture(t);
        sun->SetRotateAnimation(glm::radians(1.0f), glm::vec3(0, 0.5, 0.5));
        sun->Resize(0.1f, 0.1f, 0.1f);
        sun->MoveTo(pos.x, pos.y, pos.z);
        addDrawableObject(sun);
    }

    
    
    for (int i = 0; i < totalTrees; ++i) {
        DrawableObject* treeObj = CreateDrawableObject(treeModel, shaderProgramColor,"normal");
        treeObj->setColor(glm::vec4(0.2f, 0.5f, 0.2f, 1.0f));
        Texture* t = new Texture();
        treeObj->AddTexture(t);
        int row = i / treeCols;
        int col = i % treeCols;

        float x = -1.0f + col * 0.5f;
        float y = 0.0f;
        float z = -1.0f + row * 0.5f;

        treeObj->Resize(0.1f, 0.1f, 0.1f);
        treeObj->MoveTo(x, y, z);
        addDrawableObject(treeObj);
    }

    int bushRows = 10;
    int bushCols = 5;
    for (int i = 0; i < totalBushes; ++i) {
        DrawableObject* bushObj = CreateDrawableObject(bushModel, shaderProgramColor,"normal");
        bushObj->setColor(glm::vec4(0.6f, 0.9f, 0.6f, 1.0f));
        Texture* t = new Texture();
        bushObj->AddTexture(t);
        int row = i / bushCols;
        int col = i % bushCols;

        float x = -1.0f + col * 0.4f;
        float y = 0.05f;
        float z = 0.5f + row * 0.4f;

        bushObj->Resize(0.3f, 0.3f, 0.3f);
        bushObj->MoveTo(x, y, z);
        addDrawableObject(bushObj);
    }

    addDrawableObject(l1);
    addDrawableObject(l2);
    addDrawableObject(a);
    addDrawableObject(newReflector);

    

    
    return true;
}

bool Scene::prepareTestSceneCv05T6(){


    Shader* vr = new Shader();
    Shader* fr = new Shader();
    vr->createShaderFromFile(GL_VERTEX_SHADER, "vertex_shader_ph.glsl");
    fr->createShaderFromFile(GL_FRAGMENT_SHADER, "fragment_shader_blph.glsl");

    this->camera = this->CreateCamera();

    ShaderProgram* shaderProgramColor = new ShaderProgram(vr, fr);
    addShaderProgram(shaderProgramColor);

   


    Model* catModel = modelManager->GetModelByName("cat");


    
    


   
   

    pointLight* l2 = new pointLight(glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec4(1.0, 1.0, 1.0, 1.0),
        glm::vec4(0.95, 0.55, 0.15, 1.0),
        0.6f,
        32.0f,
        0.05f);
    


    ambientLight* a = new ambientLight(glm::vec4(0.1, 0.1, 0.1, 1.0));


  

    Texture* skyboxTexture = new Texture("sunset.jpg", "skyTexture");

    Model* skyModel = modelManager->GetModelByName("skyDom");


    Shader* vrS = new Shader();
    Shader* frS = new Shader();
    vrS->createShaderFromFile(GL_VERTEX_SHADER, "vertex_shader_skydom.glsl");
    frS->createShaderFromFile(GL_FRAGMENT_SHADER, "fragment_shader_skydom.glsl");
    ShaderProgram* shaderProgramSky = new ShaderProgram(vrS, frS);
    addShaderProgram(shaderProgramSky);

    drawableSky* sky = new drawableSky(skyModel, shaderProgramSky);
    sky->AddTexture(skyboxTexture);
    addDrawableObject(sky);








    camera->AddObserver(shaderProgramColor);
    
   
    camera->AddObserver(shaderProgramSky);
    
 
    l2->AddObserver(shaderProgramColor);
    a->AddObserver(shaderProgramColor);
  

 

    camera->UpdateMatrix();
 
    l2->UpdateLightsShaderPro();
    a->UpdateLightsShaderPro();
  
    

    Model* planeModel = modelManager->GetModelByName("plane");


    DrawableObject* bushPlane = CreateDrawableObject(planeModel, shaderProgramColor, "simplePlane");

    Texture* t6 = new Texture("grass.jpg", "texture_test");
    bushPlane->AddTexture(t6);

    bushPlane->Resize(12.0f, 12.0f, 12.0f);
   bushPlane->MoveTo(0.0f, 4.7f, 10.0f);
    addDrawableObject(bushPlane);


   


    Material* Mat = this->CreateMaterial(
        glm::vec4(0.1f, 0.1f, 0.1f, 1.0f),   // ambient
        glm::vec4(0.8f, 0.8f, 0.8f, 1.0f),   // diffuseh
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),  // specular
        5.0f    // shiness
    );

   

    int totalCat = 15;
  


    int treeRows = 3;
    int treeCols = 5;





    



    for (int i = 0; i < totalCat; ++i) {
        DrawableObject* treeObj = CreateDrawableObject(catModel, shaderProgramColor, "cat");
        treeObj->setColor(glm::vec4(0.9f, 0.6f, 0.0f, 1.0f));
        Texture* t = new Texture();
        treeObj->AddTexture(t);
        int row = i / treeCols;
        int col = i % treeCols;

        float x = -1.0f + col * 0.5f;
        float y = 0.0f;
        float z = -1.0f + row * 0.5f;

        treeObj->Resize(0.01f, 0.01f, 0.01f);
        treeObj->MoveTo(x, y, z);
        treeObj->moveOnLine(0.001f);
        addDrawableObject(treeObj);
    }

  

  
    addDrawableObject(l2);
    addDrawableObject(a);
 



    return true;
}

void Scene::createModelsForScenes() {

    const int sphereSize = sizeof(sphere) / sizeof(sphere[0]);
    std::vector<Vertex> sphereV = FromFloat(sphere, sphereSize, false, true);
  
    std::vector<std::string> faces = {
    "skybox/posx.jpg",
    "skybox/negx.jpg",
    "skybox/posy.jpg",
    "skybox/negy.jpg",
    "skybox/posz.jpg",
    "skybox/negz.jpg"
    };

    const int cubeSize = sizeof(skycube) / sizeof(skycube[0]);
    std::vector<Vertex> sunss = FromFloat(skycube, cubeSize, false, false);
    modelManager->CreateModel(sunss.data(), sunss.size(), "triangles", "skyCube");
  

    modelManager->CreateModel(sphereV.data(), sphereV.size(), "triangles", "sphere");

    std::vector<Vertex> form = this->LoadModelFromObjectFile("formula1.obj");
    modelManager->CreateModel(form.data(), form.size(), "triangles", "formule");

    const Vertex planeVertices[] = {
        // pozice                   normal                     uv
        {{-2.0f, -0.4f, 0.0f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{ 2.0f, -0.4f, 0.0f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}, {100.0f, 0.0f}},
        {{ 2.0f, -0.4f, 2.5f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}, {100.0f, 100.0f}},

        {{ 2.0f, -0.4f, 2.5f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}, {100.0f, 100.0f}},
        {{-2.0f, -0.4f, 2.5f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}, {0.0f, 100.0f}},
        {{-2.0f, -0.4f, 0.0f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.0f}}
    };


    const int treeSize = sizeof(tree) / sizeof(tree[0]);
    std::vector<Vertex> treeV = FromFloat(tree, treeSize, false, true);


    



    const int bushSize = sizeof(bushes) / sizeof(bushes[0]);

    std::vector<Vertex> bushV = FromFloat(bushes, bushSize, false, true);

    


    modelManager->CreateModel(treeV.data(), treeV.size(), "triangles", "tree");


    modelManager->CreateModel(bushV.data(), bushV.size(), "triangles", "bush");

    std::vector<Vertex> skydome = this->LoadModelFromObjectFile("skydome.obj");
    modelManager->CreateModel(skydome.data(), skydome.size(), "triangles", "skyDom");

    modelManager->CreateModel(planeVertices, sizeof(planeVertices) / sizeof(Vertex), "triangles", "plane");

    std::vector<Vertex> shrek = this->LoadModelFromObjectFile("shrek.obj");
    modelManager->CreateModel(shrek.data(), shrek.size(), "triangles", "shrek");

    std::vector<Vertex> fiona = this->LoadModelFromObjectFile("fiona.obj");
    modelManager->CreateModel(fiona.data(), fiona.size(), "triangles", "fiona");


    std::vector<Vertex> cat = this->LoadModelFromObjectFile("fatcat.obj");
    modelManager->CreateModel(cat.data(), cat.size(), "triangles", "cat");

}