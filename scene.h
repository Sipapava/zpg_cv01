#pragma once

#include "miniaudio.h"
#include <vector>

#include "shaderProgram.h"
#include "drawableObject.h"
#include "drawableSky.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "camera.h"
#include "texture.h"
#include "pointLight.h"
#include "directLight.h"
#include "reflectorLight.h"
#include "ambientLight.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "material.h"
#include "modelManager.h"


class Scene {
private:
    Camera* camera;
    std::vector<ShaderProgram*> shaderPrograms;   
    std::vector<DrawableObject*> drawableObjects; 
    std::vector<Light*> lights;
    ModelManager* modelManager;
    std::vector<Material*> materials;

    int id;                     
    static int nextId;
    std::string type;
    int score;

    ma_engine engine;

public:
    Scene(ModelManager* mM,std::string type);
    ~Scene();

    void addShaderProgram(ShaderProgram* sp);  
    //void deleteShaderProgram(ShaderProgram* sp);
    
    void addDrawableObject(DrawableObject* obj);
    void addDrawableObject(Light* lightObj);
    void addModel(Model* m);
    void AddLight(Light* l);
    void draw();
    int getId() const { return id; }
    Camera* getCamera() { return camera; }
    ShaderProgram* getShaderProgram(int index) { return shaderPrograms[index]; }
    bool DeleteObject(int id);
    bool BuildObject(int x, int y, float depht);
    bool BuildObject(float x, float y, float z);
    

    DrawableObject* CreateDrawableObject(Model* m, ShaderProgram* sp, std::string type);
    Material* CreateMaterial(const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular, const float shin);
    
    std::vector<Vertex> LoadModelFromObjectFile(const char* path);
    std::vector<Vertex> FromFloat(const float* data, size_t size, bool hasTexture, bool hasNormal);
    Camera* CreateCamera();
    void createModelsForScenes();


    //Light* CreateLight(const glm::vec3& position, const glm::vec4& colorSpecular, float intesnity, float shiness, const glm::vec4& colorDiffuse, float attenuation, const glm::vec4& ambientColor);
    bool prepareTestSceneCv05T1(); //move to factory
    bool prepareTestSceneCv05T2();
    bool prepareTestSceneCv05T3();
    bool prepareTestSceneCv05T4();
    bool prepareTestSceneCv05T6();
   
};
