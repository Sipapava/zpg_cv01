#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Observer.h"
#include <unordered_map>
#include<string>

class Light;



class ShaderProgram : public Observer {
private:
    bool updatedCamera; //nastaveno na false ve vychozim,
    bool updatedLight;
    glm::mat4* view;
    glm::mat4* projection;
    glm::vec3 cameraPos;
   

    //buffery na cameru a svetla jsou ok
    //tahle optimalizace ok
    std::vector<ShaderLightSlot> lightsSlots;

    std::unordered_map<int, int> lightIdToIndex; //index muzeme pripojit ke slotum
    int nextFreeLightIndex = 0;
         
    Shader* vertexShader;     
    Shader* fragmentShader;  
    GLuint shaderProgram;    

public:
    ShaderProgram(Shader* vertex,Shader* fragment);
    ~ShaderProgram();
    bool setUniform(const glm::mat4& matrix);
    bool setUniform(const glm::mat4& matrix,const char* spMatrix); 
    bool setUniform3(const glm::vec3& cameraPos);
    bool setUniform3(const glm::vec3& vector, const char* spVector);
    bool setUniform4(const glm::vec4& vector, const char* spVector);
    bool setUniformInt(int value, const char* name);
   
    bool setUniformFloat(float value, const char* name);
    void Notify(NotifyType type, void* data);
    void ProjectionApply();
    void ProjectionApplySky();
    void LightApply();
    

    bool setShaderProgram();
    bool resetShaderProgram();
};


