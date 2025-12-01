#pragma once
#include "Vertex.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <string.h>
#include <iostream>
#include <cstddef> // pro offsetof
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>



class Model {
private:
    GLuint VAO;
    GLuint VBO;
    std::vector<Vertex> points;
    size_t vertexCount;   
    std::string type;
    std::string name;

public:
    Model(const float* data, size_t size, bool hasTexture, bool hasNormal, std::string type,std::string name);
    Model(const char* file, std::string type, std::string name);
    ~Model();
    void Draw();
    glm::vec3 ComputeInitialCenter() const;
    std::string getName();
    std::vector<Vertex> FromFloat(const float* data, size_t size, bool hasTexture, bool hasNormal);
    std::vector<Vertex> LoadModelFromObjectFile(const char* path);
};
