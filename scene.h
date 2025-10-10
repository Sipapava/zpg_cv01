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

    DrawableObject* CreateDrawableObject(Model* m, ShaderProgram* sp);
    Model* CreateModel(const Vertex* vertices, size_t count,bool color,std::string type);
    bool prepareTestSceneCv03T1();
    bool prepareTestSceneCv03T2();
    bool prepareTestSceneCv03T3();
    //bude metodat na fill Camera with Shaders ktera se zavola po vytvoreni a pridani shadery z Sceny, musime pak osetri i mazani shaderu;
};
