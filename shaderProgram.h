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
    bool updateCamera; //nastaveno na false ve vychozim,
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
    void UpdateCamera(); //
    void ProjectionApply();

    bool setShaderProgram(); //pokud boolCamera false, nastavi uniformy projekce a view z kamery, a prepne na true
    //bude mit metodu update ktera nastavi unifmory projekce a view
};


/*
matrixID = glGetUniformLocation(shaderProgram, "viewMatrix");
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(M));

        M = glm::perspective(45.0f, 800.f / 600.f, 0.1f, 100.0f);
        matrixID = glGetUniformLocation(shaderProgram, "projectMatrix");
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(M));

*/