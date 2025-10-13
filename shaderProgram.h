#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "camera.h"

class Camera;

class ShaderProgram {
private:
    bool updatedCamera; //nastaveno na false ve vychozim,
    Camera* camera; 
    Shader* shader;          
    GLuint vertexShader;     
    GLuint fragmentShader;   
    GLuint shaderProgram;    

public:
    ShaderProgram(Shader* shaderObj, Camera* camera);
    ~ShaderProgram();
    bool setUniform(const glm::mat4& matrix);
    bool setUniform(const glm::mat4& matrix,const char* spMatrix); 
    void UpdateCamera(); 
    void ProjectionApply();

    bool setShaderProgram(); 
};


