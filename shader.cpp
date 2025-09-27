#include "Shader.h"

// Prázdný konstruktor
Shader::Shader() : vertexShader(nullptr), fragmentShader(nullptr) {}

// Konstruktor s nastavením shaderù
Shader::Shader(const char* vertex, const char* fragment)
    : vertexShader(vertex), fragmentShader(fragment) {}

// Setter
void Shader::setShaders(const char* vertex, const char* fragment) {
    vertexShader = vertex;
    fragmentShader = fragment;
}

// Gettery
const char* Shader::getVertexShader() const {
    return vertexShader;
}

const char* Shader::getFragmentShader() const {
    return fragmentShader;
}

/*







const char* vertex_shader = //program bezici pro kazdy vrchol
"#version 330\n"
"layout(location=0) in vec3 vp;" //vtupni atribut vrcholu, tento atribut je propojen s prvnim atributem vao
"void main () {"
"     gl_Position = vec4 (vp, 1.0);" //prevod na homogenni souradnici
"}";

const char* fragment_shader = //pro kazdy fragment trojuhelniku
"#version 330\n"
"out vec4 fragColor;" //vystupni barva fragmentu
"void main () {"
"     fragColor = vec4 (0.5, 0.0, 0.5, 1.0);" //nastaveni barvy
"}";
*/