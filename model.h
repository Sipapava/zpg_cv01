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
    const Vertex* points;       
    size_t vertexCount;   
    std::string type;

public:
    

    Model(const Vertex* vertices, size_t count,bool color,std::string type);

    
    ~Model();

    
    void Draw();
};
