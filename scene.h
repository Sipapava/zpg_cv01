#pragma once
#include <vector>
#include "shaderProgram.h"
#include "drawableObject.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "camera.h"
class Scene {
private:
    Camera* camera;
    std::vector<ShaderProgram*> shaderPrograms;   
    std::vector<DrawableObject*> drawableObjects; 
    
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
    void draw();
    int getId() const { return id; }
    Camera* getCamera() { return camera; }
    

    DrawableObject* CreateDrawableObject(Model* m, ShaderProgram* sp);
    Model* CreateModel(const Vertex* vertices, size_t count,bool color,std::string type);
    Camera* CreateCamera();
    bool prepareTestSceneCv03T1();
    bool prepareTestSceneCv03T2();
    bool prepareTestSceneCv04T1();
   
};
