#pragma once
#include "Vertex.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <cstddef> // pro offsetof

class Model {
private:
    GLuint VAO;
    GLuint VBO;
    const Vertex* points;       // ukazatel na pole vrcholù
    size_t vertexCount;   // poèet vrcholù

public:
    // Konstruktor: pøijímá pole vrcholù a jejich poèet
    Model(const Vertex* vertices, size_t count);

    // Destruktor – uvolní VAO a VBO
    ~Model();

    // vykreslení
    void Draw();
};
