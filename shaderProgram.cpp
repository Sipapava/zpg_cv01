#include "ShaderProgram.h"
#include <cstdio>

ShaderProgram::ShaderProgram(Shader* shaderObj)
    : shader(shaderObj), vertexShader(0), fragmentShader(0), shaderProgram(0)
{
    // Vytvoøení a kompilace vertex shaderu
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexSource = shader->getVertexShader();
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Kontrola kompilace vertex shaderu
    GLint vStatus;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vStatus);
    if (vStatus == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* infoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(vertexShader, infoLogLength, NULL, infoLog);
        fprintf(stderr, "Vertex Shader compilation failed: %s\n", infoLog);
        delete[] infoLog;
    }

    // Vytvoøení a kompilace fragment shaderu
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSource = shader->getFragmentShader();
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Kontrola kompilace fragment shaderu
    GLint fStatus;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fStatus);
    if (fStatus == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* infoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(fragmentShader, infoLogLength, NULL, infoLog);
        fprintf(stderr, "Fragment Shader compilation failed: %s\n", infoLog);
        delete[] infoLog;
    }

    // Vytvoøení shader programu
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Kontrola linkování
    GLint status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Shader Program linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }
}

ShaderProgram::~ShaderProgram() {
  
}

bool ShaderProgram::setShaderProgram() {
    if (shaderProgram != 0) {
        glUseProgram(shaderProgram);
        return true;
    }
    return false;
}
