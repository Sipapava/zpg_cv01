#include "Model.h"

Model::Model(const Vertex* vertices, size_t count,bool color,std::string type)
    : points(vertices), vertexCount(count), type(type)
{
    // Vertex Buffer Object (VBO)
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, points, GL_STATIC_DRAW);

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

    if(color){
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1,
            4,
            GL_FLOAT, GL_FALSE,
            sizeof(Vertex), //pocet bajtu celeho vertexu, o kolik skocit na dalsi
            (GLvoid*)offsetof(Vertex, color) //offsefof vrati pocet bajru od zacatku struktury k poli
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
        glDrawArrays(GL_TRIANGLES, 0,vertexCount); //size_t nevadi?
    }
    else if (type.compare("lines") == 0)
    {
        glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
    }
}
    
