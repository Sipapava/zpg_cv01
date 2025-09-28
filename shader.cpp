#include "Shader.h"



Shader::Shader(const char* vertex, const char* fragment)
    : vertexShader(vertex), fragmentShader(fragment) {}




const char* Shader::getVertexShader() const {
    return vertexShader;
}

const char* Shader::getFragmentShader() const {
    return fragmentShader;
}









