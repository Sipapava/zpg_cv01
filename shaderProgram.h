#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Observer.h"


//v shaderu musim eaktualizovat normalu a viewPos pro ten phonguv model
//normla z ertex do framnet shaderu
//podle barvy se da zjisti problem
//proste fragColor = neco;
//normala vuci kladne kdyz zaporna muzu zahoit
//if svetlo z druhe strany bacha, odlesk, cosinus zaporny ne
//duha viz prednaska
//pokud se mi lambert toci tak normala bude asi problem, takze se bude svetlo tocit
//mesic kolem zeme bude problem
//transformaci pro zemi rozsirime o transformaci o mesic,compositem by to melo jit
class ShaderProgram : public Observer{
private:
    bool updatedCamera; //nastaveno na false ve vychozim,
    bool updatedLight; 
    glm::mat4 view;
    glm::mat4 projection;
    glm::vec3 cameraPos;

    glm::vec3 positionLight;
    glm::vec4 colorLight;
    float specularIntesity;
    float shiness;
         
    Shader* vertexShader;     //nebude muset drzet
    Shader* fragmentShader;  //nebude muset drzet 
    GLuint shaderProgram;    

public:
    ShaderProgram(Shader* vertex,Shader* fragment);
    ~ShaderProgram();
    bool setUniform(const glm::mat4& matrix);
    bool setUniform(const glm::mat4& matrix,const char* spMatrix); 
    bool setUniform3(const glm::vec3& cameraPos);
    bool setUniform3(const glm::vec3& vector, const char* spVector);
    bool setUniform4(const glm::vec4& vector, const char* spVector);
   
    bool setUniformFloat(float value, const char* name);
    void Notify(const glm::mat4& view, const glm::mat4& projection) override;
    void Notify(const glm::vec3& vector,std::string type) override;
    void Notify(const glm::vec3& position, const glm::vec4& color, float intesnity, float shiness) override;
    void ProjectionApply();
    void LightApply();
    

    bool setShaderProgram(); 
};


