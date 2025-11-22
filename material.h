#pragma once
#include "glm/glm.hpp"



class Material
{
private:
    glm::vec4 ambientColor;
    glm::vec4 diffuseColor;
    glm::vec4 specularColor;
    float shinnines;

public:
    Material();
    Material(const glm::vec4& ambient,
        const glm::vec4& diffuse,
        const glm::vec4& specular,
        const float shin);

    const glm::vec4& getAmbientColor() const;
    const glm::vec4& getDiffuseColor() const;
    const glm::vec4& getSpecularColor() const;
    const float getShinnines() const;

    void setAmbientColor(const glm::vec4& v);
    void setDiffuseColor(const glm::vec4& v);
    void setSpecularColor(const glm::vec4& v);
    void setShinnines(const float v);
};