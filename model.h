#pragma once
#include "Vertex.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <cstddef> // pro offsetof

class Model {
private:
    GLuint VAO;
    GLuint VBO;
    const Vertex* points;       // ukazatel na pole vrchol�
    size_t vertexCount;   // po�et vrchol�

public:
    // Konstruktor: p�ij�m� pole vrchol� a jejich po�et
    Model(const Vertex* vertices, size_t count);

    // Destruktor � uvoln� VAO a VBO
    ~Model();

    // vykreslen�
    void Draw();
};
