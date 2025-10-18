#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "Shader.h"
#include "glm/glm.hpp"
#include <iostream>
#include <fstream>
#include <stdio.h>

class Shader {
private:
    GLuint shaderID;

public:
    Shader();
    ~Shader();
    void createShader(GLenum shaderType, const char* shaderCode);
    void createShaderFromFile(GLenum shaderType, const char* shaderFile);

    void attachShader(GLuint idShaderProgram);
};

