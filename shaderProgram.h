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
    //setUnifrom metoda pretizena,string name,glm3 vector
    //udela se GLint id - glunfirm
    //kotnrola cisla
    //pak gl uniforMatrix4v4g
    //vzdy tam musi prijit alespon jendotkova matice

    bool setShaderProgram();
};
