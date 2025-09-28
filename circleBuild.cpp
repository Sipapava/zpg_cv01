

#include "circleBuild.h"

//kresli se spis oval, nutno protahnout nejakou normalizaci

std::vector<Vertex> buildCircle(float radius, int vCount)
{
    std::vector<glm::vec3> temp;
    std::vector<Vertex> vertices;

    
    Vertex center;
    center.pos = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    center.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

    
    for (int i = 0; i < vCount; i++)
    {
        float angle = 360.0f / vCount * i;
        float x = radius * cos(glm::radians(angle));
        float y = radius * sin(glm::radians(angle));
        temp.push_back(glm::vec3(x, y, 0.0f));
    }

    
    for (int i = 0; i < vCount - 1; i++)
    {
        Vertex v1, v2;
        v1.pos = glm::vec4(temp[i], 1.0f);
        v1.color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

        v2.pos = glm::vec4(temp[i + 1], 1.0f);
        v2.color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

        vertices.push_back(center);
        vertices.push_back(v1);
        vertices.push_back(v2);
    }

    
    Vertex last, first;
    last.pos = glm::vec4(temp[vCount - 1], 1.0f);
    last.color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

    first.pos = glm::vec4(temp[0], 1.0f);
    first.color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

    vertices.push_back(center);
    vertices.push_back(last);
    vertices.push_back(first);

    return vertices;
}


