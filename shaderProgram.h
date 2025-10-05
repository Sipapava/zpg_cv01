#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class ShaderProgram {
private:
    Shader* shader;          
    GLuint vertexShader;     
    GLuint fragmentShader;   
    GLuint shaderProgram;    

public:
    ShaderProgram(Shader* shaderObj);
    ~ShaderProgram();
    bool setUniform(const glm::mat4& matrix);
    bool setUniform(const glm::mat4& matrix,const char* spMatrix); 
  

    bool setShaderProgram();
};
