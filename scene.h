#pragma once
#include <vector>
#include "shaderProgram.h"
#include "drawableObject.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "camera.h"
#include "light.h"
class Scene {
private:
    Camera* camera;
    std::vector<ShaderProgram*> shaderPrograms;   
    std::vector<DrawableObject*> drawableObjects; 
    std::vector<Light*> lights;
    std::vector<Model*> models;

    int id;                     
    static int nextId;

public:
    Scene();
    ~Scene();

    void addShaderProgram(ShaderProgram* sp);  
    //void deleteShaderProgram(ShaderProgram* sp);
    
    void addDrawableObject(DrawableObject* obj);
    void addModel(Model* m);
    void AddLight(Light* l);
    void draw();
    int getId() const { return id; }
    Camera* getCamera() { return camera; }
    ShaderProgram* getShaderProgram(int index) { return shaderPrograms[index]; }

    

    DrawableObject* CreateDrawableObject(Model* m, ShaderProgram* sp);
    Model* CreateModel(const Vertex* vertices, size_t count,bool color,std::string type);
    Camera* CreateCamera();
    Light* CreateLight(const glm::vec3& position, const glm::vec4& color, float intesnity, float shiness);
    bool prepareTestSceneCv05T1(); //presunout do tovarny
    bool prepareTestSceneCv05T2();
    bool prepareTestSceneCv05T3();
    bool prepareTestSceneCv05T4();
   
};
