#include "Model.h"

Model::Model(const Vertex* vertices, size_t count, std::string type)
    : vertexCount(count), type(type)
{
    // Vertex Buffer Object (VBO)

    points = new Vertex[vertexCount];       // alokace vlastního bufferu
    for (size_t i = 0; i < vertexCount; ++i) {
    points[i].pos     = glm::vec4(vertices[i].pos);
    points[i].normal  = glm::vec4(vertices[i].normal);
    points[i].texture = glm::vec2(vertices[i].texture);
}


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

   
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1,
            4,
            GL_FLOAT, GL_FALSE,
            sizeof(Vertex), //number of bytes of the entire vertex, how much to jump to the next one
            (GLvoid*)offsetof(Vertex, normal) //offsefof returns the number of bytes from the beginning of the structure to the array
        );
    

   

     // Atribut textury (location = 2)
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2,
        2,                      // vec2
        GL_FLOAT, GL_FALSE,
        sizeof(Vertex),
        (GLvoid*)offsetof(Vertex, texture)
    );
    

}

Model::Model(const Vertex* vertices, size_t count, std::string type,std::string specialCase)
    :  vertexCount(count), type(type)
{
    points = new Vertex[vertexCount];       // alokace vlastního bufferu
    for (size_t i = 0; i < vertexCount; ++i) {
        points[i].pos = glm::vec4(vertices[i].pos);
        points[i].normal = glm::vec4(vertices[i].normal);
        points[i].texture = glm::vec2(vertices[i].texture);
    }
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


     // Atribut textury (location = 2)
    if (specialCase.compare("skyDom") == 0) {
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
