#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "Shader.h"

class ShaderProgram {
private:
    Shader* shader;          
    GLuint vertexShader;     
    GLuint fragmentShader;   
    GLuint shaderProgram;    

public:
    ShaderProgram(Shader* shaderObj);
    ~ShaderProgram();

    bool setShaderProgram();
};
