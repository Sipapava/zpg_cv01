#include "ShaderProgram.h"
#include <cstdio>

ShaderProgram::ShaderProgram(Shader* vertex,Shader* fragment) //musi dostat fragment a vertex
    : vertexShader(vertex), fragmentShader(fragment), shaderProgram(0)
{
    updatedCamera = false;
    updatedLight = false;
    view  = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);
    cameraPos = glm::vec3(0.0f, 0.5f, -2.0f);

    // Shadery vytvarime venku

   

    
    shaderProgram = glCreateProgram();
    vertexShader->attachShader(shaderProgram);
    fragmentShader->attachShader(shaderProgram);
    glLinkProgram(shaderProgram);

    
    GLint status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Shader Program linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
        //pridat return na false;
    }
}

ShaderProgram::~ShaderProgram() {
    delete vertexShader;
    delete fragmentShader;
}

bool ShaderProgram::setShaderProgram() { 
    if (shaderProgram != 0) {
       
            glUseProgram(shaderProgram);
            
        return true;
    }
    return false;
}

bool ShaderProgram::setUniform(const glm::mat4& matrix) {
    GLint id = glGetUniformLocation(shaderProgram, "modelMatrix"); 
    if (id >= 0) { 
        glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(matrix));
        return true;
    }
    return false;
}

bool ShaderProgram::setUniform(const glm::mat4& matrix, const char* spMatrix) {
    GLint id = glGetUniformLocation(shaderProgram, spMatrix); 
    if (id >= 0) { 
        glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(matrix));
        return true;
    }
    return false;
}


bool ShaderProgram::setUniform3(const glm::vec3& cameraPos) {
    GLint id = glGetUniformLocation(shaderProgram, "cameraPos");
    if (id >= 0) {
        glUniform3fv(id, 1, glm::value_ptr(cameraPos));
       
        return true;
    }
    return false;
}

bool ShaderProgram::setUniform3(const glm::vec3& vector, const char* spVector) {
    GLint id = glGetUniformLocation(shaderProgram, spVector);
    if (id >= 0) {
        glUniform3fv(id, 1, glm::value_ptr(vector)); 
      
        return true;
    }
    return false;
}


bool ShaderProgram::setUniform4(const glm::vec4& vector, const char* spVector) {
    GLint id = glGetUniformLocation(shaderProgram, spVector);
    if (id >= 0) {
        glUniform4fv(id, 1, glm::value_ptr(vector));
        
        return true;
    }
    return false;
}

bool ShaderProgram::setUniformFloat(float value, const char* name) {
    GLint id = glGetUniformLocation(shaderProgram, name);
    if (id >= 0) {
        glUniform1f(id, value);
       
        return true;
    }
    return false;
}


//nova metoda setUniform por svetlo
void ShaderProgram::Notify(const glm::mat4& view, const glm::mat4& projection) {
    updatedCamera = false;
    this->projection = projection;
    this->view = view;
    
}; 


void ShaderProgram::Notify(const glm::vec3& vector,std::string type) { //pridame string
    if (type.compare("cameraPos") == 0) {
        updatedCamera = false;
        this->cameraPos = vector;
    }
    

}

void ShaderProgram::Notify(const glm::vec3& position, const glm::vec4& color, float intesnity, float shiness) {
    updatedLight = false;
    this->positionLight = position;
    this->colorLight = color;
    this->specularIntesity = intesnity;
    this->shiness = shiness;
}



void ShaderProgram::LightApply() {

    if (!updatedLight) {
       
        this->setUniform3(positionLight,"lightPosition");
        this->setUniform4(colorLight,"lightColor");
        this->setUniformFloat(specularIntesity, "specularIntensity");
        this->setUniformFloat(shiness, "shiness");
        updatedLight = true;
    }
}


void ShaderProgram::ProjectionApply() {

    if (!updatedCamera) {
        
        this->setUniform3(cameraPos);
       
        this->setUniform(view,"viewMatrix");
        this->setUniform(projection,"projectMatrix");
        updatedCamera = true;
    }
}
