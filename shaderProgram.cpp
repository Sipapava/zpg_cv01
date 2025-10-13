#include "ShaderProgram.h"
#include <cstdio>

ShaderProgram::ShaderProgram(Shader* shaderObj, Camera* camera)
    : shader(shaderObj), vertexShader(0), fragmentShader(0), shaderProgram(0),camera(camera)
{
    updatedCamera = false;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexSource = shader->getVertexShader();
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    
    
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSource = shader->getFragmentShader();
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

   

    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
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
    delete shader;
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

void ShaderProgram::UpdateCamera() {
    updatedCamera = false;
    
}; 
void ShaderProgram::ProjectionApply() {

    if (!updatedCamera) {
        glm::mat4 Mv = camera->getViewMatrix();
        glm::mat4 Mp = camera->getProjectionMatrix();
        
        this->setUniform(Mv,"viewMatrix");
        this->setUniform(Mp,"projectMatrix");
        updatedCamera = true;
    }
}
