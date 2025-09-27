#pragma once

class Shader {
private:
    const char* vertexShader;
    const char* fragmentShader;

public:
    Shader();
    Shader(const char* vertex, const char* fragment);

    void setShaders(const char* vertex, const char* fragment);

    const char* getVertexShader() const;
    const char* getFragmentShader() const;
};
