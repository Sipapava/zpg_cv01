#pragma once

class Shader {
private:
    const char* vertexShader;
    const char* fragmentShader;

public:
    
    Shader(const char* vertex, const char* fragment);


    const char* getVertexShader() const;
    const char* getFragmentShader() const;
};

