
#define MINIAUDIO_IMPLEMENTATION
#include "Scene.h"
#include <algorithm> 


//remake create and add methods for DrObj and Shaders

int Scene::nextId = 0;
Scene::Scene(ModelManager* mM,std::string type) {
    id = nextId++;
    camera = nullptr;
    srand(static_cast<unsigned int>(time(nullptr)));
    ma_engine_init(NULL, &engine);
    modelManager = mM;
    this->type = type;
    score = 1;
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
                ma_engine_play_sound(&this->engine, "sounds/hurt.mp3", NULL);
            }
            else if (obj->GetType() == "cat") {
                ma_engine_play_sound(&this->engine, "sounds/cat.wav", NULL);
            }
            else if (obj->GetType() == "spinosaurus") {
                ma_engine_play_sound(&this->engine, "sounds/spinosaurus.mp3", NULL);
            }
            else {
                ma_engine_play_sound(&this->engine, "sounds/hit.mp3", NULL);
            }

            delete obj;
            it = drawableObjects.erase(it);
            if (this->type == "game") {
                score++;
                std::cout << "Score adds up: " << this->score << std::endl;
                if (score % 5 == 0) {
                    this->buildSpinosaurus();
                   
                    return true;
                }

                if (this->drawableObjects.size() == 4) {
                    std::cout << "YOU CATCH THEM ALL! "<< std::endl;
                }
            }
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

    
    
    ma_engine_play_sound(&engine, "sounds/plantSound.mp3", NULL);

    return true;
}

void Scene::buildSpinosaurus() {
    Model* spinoModel = modelManager->GetModelByName("spinosaurus");
    ShaderProgram* shaderProgramColor = shaderPrograms[0];
    DrawableObject* spObj = CreateDrawableObject(spinoModel, shaderProgramColor, "spinosaurus");
    spObj->setColor(glm::vec4(0.33f, 0.2f, 0.8f, 1.0f));
    Texture* t = new Texture();
    spObj->AddTexture(t);
    float r = 0 + (rand() / (float)RAND_MAX) * (359 - 0);

    float x = -2.0f + (rand() / (float)RAND_MAX) * 4.0f;;
    float y = -0.2f;
    float z = -2.0f + (rand() / (float)RAND_MAX) * 4.0f;


    spObj->Rotate(glm::radians(-90.0f), 1, 0, 0); // srovná Z-up -> Y-up
    spObj->Rotate(glm::radians(90.0f), 0, 1, 0);
    spObj->Rotate(glm::radians(r), 0, 1, 0);
    spObj->Resize(0.005f, 0.005f, 0.005f);
    spObj->MoveTo(x, y, z);
    spObj->moveOnLine(0.02f);


    addDrawableObject(spObj);
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


bool Scene::prepareHomogenusChange() {

    Shader* vr = new Shader();
    Shader* fr = new Shader();
    this->camera = this->CreateCamera();
    vr->createShaderFromFile(GL_VERTEX_SHADER, "shaders/vertex_shader_phlam.glsl");
    fr->createShaderFromFile(GL_FRAGMENT_SHADER, "shaders/fragment_shader_blph.glsl");

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


 



    float intensity = 1.0f;
    

    directLight* l = new directLight(lightDirection,  intensity);



    ambientLight* a = new ambientLight();
    camera->AddObserver(shaderProgramColor);

    a->AddObserver(shaderProgramColor);
    l->AddObserver(shaderProgramColor);
    addDrawableObject(sun);
    camera->UpdateMatrix();
    addDrawableObject(a);
    addDrawableObject(l);

    return true;
}

bool Scene::prepareSolarSystem() {
    
    Shader* vr1 = new Shader();
    Shader* fr1 = new Shader();
    vr1->createShaderFromFile(GL_VERTEX_SHADER, "shaders/vertex_shader_phlam.glsl");
    fr1->createShaderFromFile(GL_FRAGMENT_SHADER, "shaders/fragment_shader_blph.glsl");

    ShaderProgram* shaderProgramBl = new ShaderProgram(vr1, fr1);

    addShaderProgram(shaderProgramBl);

    Shader* vr2 = new Shader();
    Shader* fr2 = new Shader();
    vr2->createShaderFromFile(GL_VERTEX_SHADER, "shaders/vertex_shader_con.glsl");
    fr2->createShaderFromFile(GL_FRAGMENT_SHADER, "shaders/fragment_shader_con.glsl");

    ShaderProgram* shaderProgramCon = new ShaderProgram(vr2, fr2);

    addShaderProgram(shaderProgramCon);
   



    this->camera = this->CreateCamera();

    Model* sphereModel = modelManager->GetModelByName("planet");
    pointLight* l2 = new pointLight(sphereModel, shaderProgramCon, glm::vec3(0.0f, 0.0f, 0.0f),
      
        0.6f,
        
        0.001f);
    Texture* t2 = new Texture();
    l2->AddTexture(t2);



   ambientLight * a = new ambientLight();
  
    
   
   addDrawableObject(l2);
   addDrawableObject(a);
    camera->AddObserver(shaderProgramBl);
    l2->AddObserver(shaderProgramBl);
    a->AddObserver(shaderProgramBl);
    l2->AddObserver(shaderProgramCon);
    a->AddObserver(shaderProgramCon);


  
    
    camera->UpdateMatrix();
    l2->UpdateLightsShaderPro();
    




    Material* sunMat = this->CreateMaterial(
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),   
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),  
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),  
        5.0f   
    );
    

    

    DrawableObject* sun = CreateDrawableObject(sphereModel, shaderProgramBl,"normal");
    sun->Resize(0.4f, 0.4f, 0.4f);
    sun->SetRotateAnimation(glm::radians(0.001f), glm::vec3(0, 1, 0));
    sun->AddTexture(new Texture("textures/sun.jpg", "texture_test"));
    sun->setMaterial(sunMat);
    addDrawableObject(sun);

    DrawableObject* mercur = CreateDrawableObject(sphereModel, shaderProgramBl, "normal");
    mercur->Resize(0.05f, 0.05f, 0.05f);
    mercur->SetRotateAnimation(glm::radians(0.01f), glm::vec3(0, 1, 0));
    mercur->MoveTo(1.0f, 0.0f, 0.0f);
    mercur->SetRotateAnimation(glm::radians(4.0f), glm::vec3(0, 1, 0));
    mercur->AddTexture(new Texture("textures/mercury.jpg", "texture_test"));
    addDrawableObject(mercur);

    DrawableObject* venus = CreateDrawableObject(sphereModel, shaderProgramBl, "normal");
    venus->Resize(0.09f, 0.09f, 0.09f);
    venus->SetRotateAnimation(glm::radians(-0.05f), glm::vec3(0, 0, 1));
    venus->MoveTo(2.0f, 0.0f, 0.0f);
    venus->SetRotateAnimation(glm::radians(1.2f), glm::vec3(0, 1, 0));
    venus->AddTexture(new Texture("textures/venus.jpg", "texture_test"));
    addDrawableObject(venus);

    DrawableObject* earth = CreateDrawableObject(sphereModel, shaderProgramBl,"normal");
    earth->Resize(0.1f, 0.1f, 0.1f);
    earth->SetRotateAnimation(glm::radians(1.0f), glm::vec3(0, 0.8, -0.2));
    earth->MoveTo(3.0f, 0.0f, 0.0f);
    earth->SetRotateAnimation(glm::radians(1.0f), glm::vec3(0, 1, 0));
    earth->AddTexture(new Texture("textures/earth.jpg", "texture_test"));
    addDrawableObject(earth);

    DrawableObject* moon = CreateDrawableObject(sphereModel, shaderProgramBl,"normal");
    moon->Resize(0.05f, 0.05f, 0.05f);
    moon->SetRotateAnimation(glm::radians(1.0f), glm::vec3(0, 1, 0));
    moon->MoveTo(0.3f, 0.0f, 0.0f);
    moon->SetRotateAnimation(glm::radians(1.0f), glm::vec3(0, 1, 0));
    moon->MoveTo(3.0f, 0.0f, 0.0f);
    moon->SetRotateAnimation(glm::radians(1.0f), glm::vec3(0, 1, 0));
    moon->AddTexture(new Texture("textures/moon.jpg", "texture_test"));
    addDrawableObject(moon);

    DrawableObject* mars = CreateDrawableObject(sphereModel, shaderProgramBl, "normal");
    mars->Resize(0.09f, 0.09f, 0.09f);
    mars->SetRotateAnimation(glm::radians(1.0f), glm::vec3(0, 0.85, 0.15));
    mars->MoveTo(4.0f, 0.0f, 0.0f);
    mars->SetRotateAnimation(glm::radians(0.5f), glm::vec3(0, 1, 0));
    mars->AddTexture(new Texture("textures/mars.jpg", "texture_test"));
    addDrawableObject(mars);
    
    return true;
}

bool Scene::prepareFlyingCars() {
    Shader* vr1 = new Shader();
    Shader* fr1 = new Shader();
    vr1->createShaderFromFile(GL_VERTEX_SHADER, "shaders/vertex_shader_con.glsl");
    fr1->createShaderFromFile(GL_FRAGMENT_SHADER, "shaders/fragment_shader_con.glsl");

    Shader* vr2 = new Shader();
    Shader* fr2 = new Shader();
    vr2->createShaderFromFile(GL_VERTEX_SHADER, "shaders/vertex_shader_phlam.glsl");
    fr2->createShaderFromFile(GL_FRAGMENT_SHADER, "shaders/fragment_shader_lam.glsl");

    Shader* vr3 = new Shader();
    Shader* fr3 = new Shader();
    vr3->createShaderFromFile(GL_VERTEX_SHADER, "shaders/vertex_shader_phlam.glsl");
    fr3->createShaderFromFile(GL_FRAGMENT_SHADER, "shaders/fragment_shader_ph.glsl");


    Shader* vr4 = new Shader();
    Shader* fr4 = new Shader();
    vr4->createShaderFromFile(GL_VERTEX_SHADER, "shaders/vertex_shader_phlam.glsl");
    fr4->createShaderFromFile(GL_FRAGMENT_SHADER, "shaders/fragment_shader_blph.glsl");


   
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
    vrS->createShaderFromFile(GL_VERTEX_SHADER, "shaders/vertex_shader_cube.glsl");
    frS->createShaderFromFile(GL_FRAGMENT_SHADER, "shaders/fragment_shader_cube.glsl");
   
   
    
   

    this->camera = this->CreateCamera();
    
   
   ambientLight* a = new ambientLight();
    
   glm::vec3 lightDirection = glm::vec3(0.0f, -1.0f, 0.0f);

  
   

   
   float intensity = 1.0f;
   

   directLight* l =  new directLight(lightDirection,  intensity);

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
    
    Model* formula = modelManager->GetModelByName("formule");
    //Model* skyModel = new Model(cubeV.data(), cubeV.size(), "triangles", "cube");

    
    

    int i = 0;
    std::vector<Texture*> vv;
    Texture* t1 = new Texture("textures/wooden_fence.png", "texture_test");
    Texture* t2 = new Texture("textures/wooden_fence.png", "texture_test");
    Texture* t3 = new Texture("textures/wooden_fence.png", "texture_test");
    Texture* t4 = new Texture("textures/wooden_fence.png", "texture_test");
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

bool Scene::prepareForest(){
    
    
    
    Shader* vr = new Shader();
    Shader* fr = new Shader();
    vr->createShaderFromFile(GL_VERTEX_SHADER, "shaders/vertex_shader_phlam.glsl");
    fr->createShaderFromFile(GL_FRAGMENT_SHADER, "shaders/fragment_shader_blph.glsl");
    
    this->camera = this->CreateCamera();

    ShaderProgram* shaderProgramColor = new ShaderProgram(vr, fr);
    addShaderProgram(shaderProgramColor);

    Model* sphereModel = modelManager->GetModelByName("sphere");


    Model* treeModel = modelManager->GetModelByName("tree");


    Model* bushModel = modelManager->GetModelByName("bush");
    Shader* vr2 = new Shader();
    Shader* fr2 = new Shader();
    vr2->createShaderFromFile(GL_VERTEX_SHADER, "shaders/vertex_shader_con.glsl");
    fr2->createShaderFromFile(GL_FRAGMENT_SHADER, "shaders/fragment_shader_con.glsl");
    ShaderProgram* shaderProgramBug = new ShaderProgram(vr2, fr2);
   
    addShaderProgram(shaderProgramBug);
  
    
    pointLight* l1 = new pointLight(sphereModel,shaderProgramBug,glm::vec3(0.0f, 0.0f, 0.0f),
        
        0.6f,
        
        5.0f);

    Texture* t1 = new Texture();
    l1->AddTexture(t1);

  
    pointLight* l2 = new pointLight(sphereModel, shaderProgramBug,glm::vec3(0.0f, 0.0f, 0.0f),
       
        0.6f,
       
        5.0f);
    Texture* t2 = new Texture();
    l2->AddTexture(t2);
    

    ambientLight* a = new ambientLight( );


    reflectorLightCamera *newReflector = new reflectorLightCamera(
        glm::vec3(0.0f, 0.5f, -2.0f),               
        glm::vec3(0.0f, 0.0f, 0.0f),                   
       
        1.0f,                   
                      
        0.1f,                
        1.0f                   
    );

    Texture* skyboxTexture = new Texture("textures/sunset.jpg", "skyTexture");
   
    Model* skyModel = modelManager->GetModelByName("skyDom");


    Shader* vrS = new Shader();
    Shader* frS = new Shader();
    vrS->createShaderFromFile(GL_VERTEX_SHADER, "shaders/vertex_shader_skydom.glsl");
    frS->createShaderFromFile(GL_FRAGMENT_SHADER, "shaders/fragment_shader_skydom.glsl");
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
    vC->createShaderFromFile(GL_VERTEX_SHADER, "shaders/vertex_shader_con.glsl");
    frC->createShaderFromFile(GL_FRAGMENT_SHADER, "shaders/fragment_shader_con.glsl");
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
   
   Texture* t6 = new Texture("textures/grass.jpg", "texture_test");
   bushPlane->AddTexture(t6);

    bushPlane->Resize(10.0f, 10.0f, 10.0f);
    bushPlane->MoveTo(-2.0f, 4.0f, -2.0f);
    addDrawableObject(bushPlane);

    
    Model* shrekM = modelManager->GetModelByName("shrek");

   
    Model* fionaM = modelManager->GetModelByName("fiona");

    Texture* shrekT = new Texture("textures/shrek.png", "texture_test");
   
    Texture* fionaT = new Texture("textures/fiona.png", "texture_test");


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

bool Scene::prepareCatchGame(){


    Shader* vr = new Shader();
    Shader* fr = new Shader();
    vr->createShaderFromFile(GL_VERTEX_SHADER, "shaders/vertex_shader_phlam.glsl");
    fr->createShaderFromFile(GL_FRAGMENT_SHADER, "shaders/fragment_shader_blph.glsl");

    this->camera = this->CreateCamera();

    ShaderProgram* shaderProgramColor = new ShaderProgram(vr, fr);
    addShaderProgram(shaderProgramColor);

   


    Model* catModel = modelManager->GetModelByName("cat");


    
    


   
   

    pointLight* l2 = new pointLight(glm::vec3(0.0f, 2.0f, 0.0f),
        
        0.6f,
      
        0.005f);
    


    ambientLight* a = new ambientLight();


  

    Texture* skyboxTexture = new Texture("textures/blueSky.jpg", "skyTexture");

    Model* skyModel = modelManager->GetModelByName("skyDom");


    Shader* vrS = new Shader();
    Shader* frS = new Shader();
    vrS->createShaderFromFile(GL_VERTEX_SHADER, "shaders/vertex_shader_skydom.glsl");
    frS->createShaderFromFile(GL_FRAGMENT_SHADER, "shaders/fragment_shader_skydom.glsl");
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

    Texture* t6 = new Texture("textures/dirt.jpg", "texture_test");
    bushPlane->AddTexture(t6);

    bushPlane->Resize(12.0f, 12.0f, 12.0f);
   bushPlane->MoveTo(0.0f, 4.7f, -10.0f);
    addDrawableObject(bushPlane);


   


    Material* Mat = this->CreateMaterial(
        glm::vec4(0.1f, 0.1f, 0.1f, 1.0f),   
        glm::vec4(0.8f, 0.8f, 0.8f, 1.0f),  
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),  
        5.0f   
    );


    int totalCat = 15;
  
    int Rows = 3;
    int Cols = 5;


    for (int i = 0; i < totalCat; ++i) {
        DrawableObject* catObj = CreateDrawableObject(catModel, shaderProgramColor, "cat");
        catObj->setColor(glm::vec4(0.9f, 0.6f, 0.0f, 1.0f));
        Texture* t = new Texture();
        catObj->AddTexture(t);
        int row = i / Cols;
        int col = i % Cols;

        float x = -1.0f + col * 0.5f;
        float y = 0.0f;
        float z = -1.0f + row * 0.5f;

        float r = 0 + (rand() / (float)RAND_MAX) * (359 - 0);

        catObj->Rotate(glm::radians(r), 0, 1, 0);
        catObj->Resize(0.01f, 0.01f, 0.01f);
        catObj->MoveTo(x, y, z);
        catObj->moveOnLine(0.01f);
        addDrawableObject(catObj);
    }

  

  
    addDrawableObject(l2);
    addDrawableObject(a);
 



    return true;
}

