#pragma once
#include "Vertex.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <string.h>
#include <iostream>
#include <cstddef> // pro offsetof

class Model {
private:
    GLuint VAO;
    GLuint VBO;
    Vertex* points;       
    size_t vertexCount;   
    std::string type;
    std::string name;

public:
    

    Model(const Vertex* vertices, size_t count, std::string type,std::string name);
  

    
    ~Model();

    
    void Draw();
    glm::vec3 ComputeInitialCenter() const;
    std::string getName();
};
