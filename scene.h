#pragma once
#include <vector>
#include "shaderProgram.h"
#include "drawableObject.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Scene {
private:
    std::vector<ShaderProgram*> shaderPrograms;   
    std::vector<DrawableObject*> drawableObjects; 
    //pridat vectoru modelu

    int id;                     
    static int nextId;

public:
    Scene();
    ~Scene();

    void addShaderProgram(ShaderProgram* sp);  
    //void deleteShaderProgram(ShaderProgram* sp);

    void addDrawableObject(DrawableObject* obj);
    void draw();
    int getId() const { return id; } 

    DrawableObject* CreateDrawableObject(Model* m, ShaderProgram* sp);
    Model* CreateModel(const Vertex* vertices, size_t count,bool color,std::string type);
    bool prepareTestSceneCv02();
};
