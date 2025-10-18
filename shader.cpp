#include "Shader.h"


Shader::Shader() {
    shaderID = 0;
};
Shader::~Shader() {};

void Shader::createShader(GLenum shaderType, const char* shaderCode)
     {

    // Creates an empty shader
    shaderID = glCreateShader(shaderType);
    // Sets the source code of the shader.
    glShaderSource(shaderID, 1, &shaderCode, NULL);
    // Compiles the shader source code
    glCompileShader(shaderID);

}



void Shader::createShaderFromFile(GLenum shaderType, const char* shaderFile)
{
    //Loading the contents of a file into a variable
    std::ifstream file(shaderFile);
    if (!file.is_open())
    {
        std::cout << "Unable to open file " << shaderFile << std::endl;
        exit(-1);
    }
    std::string shaderCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    this->createShader(shaderType, shaderCode.c_str());

}

void Shader::attachShader(GLuint idShaderProgram)
{
    //Attaches the shader to the shaderProgram
    glAttachShader(idShaderProgram, shaderID);
}


