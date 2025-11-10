#pragma once
#include <string>
#include <GL/glew.h>
#include <vector>
#include <iostream>

class Texture {
public:
    GLuint id;
    std::string type;
    

    Texture(const std::string& pathFilename, const std::string& typeName);
    Texture(const std::vector<std::string>& faces, const std::string& typeName);
    Texture();
    ~Texture();
    bool BindTexture();
    bool ActiveTexture();
    int GetSlot();
    std::string& GetType();
};


