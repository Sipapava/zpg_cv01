#include "Model.h"

//unwarp a cubej objection, shade a autosmooth
Model::Model(const float* data, size_t size, bool hasTexture, bool hasNormal, std::string type, std::string name)
    :  type(type),name(name)
{
    
    size_t stride = 3 + (hasNormal ? 3 : 0) + (hasTexture ? 2 : 0);

    vertexCount = size / stride;
    points = FromFloat(data, size, hasTexture, hasNormal);


    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, points.data(), GL_STATIC_DRAW);

    // Vertex Array Object (VAO)
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Atribut pozice (location = 0)
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(
        0,
        4,
        GL_FLOAT, GL_FALSE,
        sizeof(Vertex),
        (GLvoid*)offsetof(Vertex, pos)
    );

    if (name.compare("skyCube") != 0) {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1,
            4,
            GL_FLOAT, GL_FALSE,
            sizeof(Vertex), //number of bytes of the entire vertex, how much to jump to the next one
            (GLvoid*)offsetof(Vertex, normal) //offsefof returns the number of bytes from the beginning of the structure to the array
        );
    }
    

   

     // Atribut textury (location = 2)
    if (name.compare("skyCube") != 0) {
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(
            2,
            2,                      // vec2
            GL_FLOAT, GL_FALSE,
            sizeof(Vertex),
            (GLvoid*)offsetof(Vertex, texture)
        );
    }
    

}

Model::Model(const char* file, std::string type, std::string name)
    : type(type), name(name)
{

    
    points = this->LoadModelFromObjectFile(file);
    this->vertexCount = points.size();


    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, points.data(), GL_STATIC_DRAW);

    // Vertex Array Object (VAO)
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Atribut pozice (location = 0)
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(
        0,
        4,
        GL_FLOAT, GL_FALSE,
        sizeof(Vertex),
        (GLvoid*)offsetof(Vertex, pos)
    );

    if (name.compare("skyCube") != 0) {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1,
            4,
            GL_FLOAT, GL_FALSE,
            sizeof(Vertex), //number of bytes of the entire vertex, how much to jump to the next one
            (GLvoid*)offsetof(Vertex, normal) //offsefof returns the number of bytes from the beginning of the structure to the array
        );
    }




    // Atribut textury (location = 2)
    if (name.compare("skyCube") != 0) {
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(
            2,
            2,                      // vec2
            GL_FLOAT, GL_FALSE,
            sizeof(Vertex),
            (GLvoid*)offsetof(Vertex, texture)
        );
    }


}


Model::~Model() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Model::Draw() {
    glBindVertexArray(VAO);
    if (type.compare("triangles") == 0) {
        glDrawArrays(GL_TRIANGLES, 0,vertexCount); 
    }
    else if (type.compare("lines") == 0)
    {
        glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
    }
}
    
glm::vec3 Model::ComputeInitialCenter() const {
    if (vertexCount == 0) return glm::vec3(0.0f);

    glm::vec3 sum(0.0f);
    for (size_t i = 0; i < vertexCount; ++i) {
        sum += glm::vec3(points[i].pos); 
    }

    return sum / static_cast<float>(vertexCount);
}

std::string Model::getName() {
    return this->name;
}



std::vector<Vertex> Model::LoadModelFromObjectFile(const char* path) {
    Assimp::Importer importer;
    std::vector<Vertex> vertices;

    const aiScene* scene = importer.ReadFile(path,
        aiProcess_Triangulate
    );

    if (!scene || !scene->HasMeshes()) {
        std::cerr << "Assimp error: " << importer.GetErrorString() << std::endl;
        return vertices;
    }

    for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
        aiMesh* mesh = scene->mMeshes[m];

        for (unsigned int f = 0; f < mesh->mNumFaces; ++f) {
            aiFace& face = mesh->mFaces[f];

            for (unsigned int i = 0; i < face.mNumIndices; ++i) {
                unsigned int idx = face.mIndices[i];
                Vertex v;


                v.pos = glm::vec4(
                    mesh->mVertices[idx].x,
                    mesh->mVertices[idx].y,
                    mesh->mVertices[idx].z,
                    1.0f
                );


                if (mesh->HasNormals()) {
                    v.normal = glm::vec4(
                        mesh->mNormals[idx].x,
                        mesh->mNormals[idx].y,
                        mesh->mNormals[idx].z,
                        1.0f
                    );
                }
                else {
                    v.normal = glm::vec4(0, 0, 0, 0);
                }


                if (mesh->HasTextureCoords(0)) {
                    aiVector3D tex = mesh->mTextureCoords[0][idx];
                    v.texture = glm::vec2(tex.x, tex.y);
                }
                else {
                    v.texture = glm::vec2(0.0f, 0.0f);
                }

                vertices.push_back(v);
            }
        }
    }

    return vertices;
}

std::vector<Vertex> Model::FromFloat(const float* data, size_t size, bool hasTexture, bool hasNormal) {
    std::vector<Vertex> vertices;

    // 3 (pos) + 3 (normal) + 2 (tex)
    size_t stride = 3 + (hasNormal ? 3 : 0) + (hasTexture ? 2 : 0);

    if (size % stride != 0) {
        std::cerr << " FromFloat: Data size (" << size
            << ") is not a multiple of stride (" << stride << ")!\n";
    }

    for (size_t i = 0; i < size; i += stride) {
        Vertex v;

        v.pos = glm::vec4(data[i], data[i + 1], data[i + 2], 1.0f);
        size_t offset = 3;

        if (hasNormal) {
            v.normal = glm::vec4(data[i + offset], data[i + offset + 1], data[i + offset + 2], 1.0f);
            offset += 3;
        }
        else {
            v.normal = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
        }

        if (hasTexture) {
            v.texture = glm::vec2(data[i + offset], data[i + offset + 1]);
            offset += 2;
        }
        else {
            v.texture = glm::vec2(1.0f);
        }

        vertices.push_back(v);
    }

    return vertices;
}