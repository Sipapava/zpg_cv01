#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "Shader.h"

class ShaderProgram {
private:
    Shader* shader;          // pointer na Shader s texty
    GLuint vertexShader;     // ID vertex shaderu
    GLuint fragmentShader;   // ID fragment shaderu
    GLuint shaderProgram;    // ID shader programu

public:
    ShaderProgram(Shader* shaderObj);
    ~ShaderProgram();

    bool setShaderProgram();
};
