#include "material.h"

Material::Material()
    : ambientColor(0.2f, 0.2f, 0.2f, 1.0f),  
    diffuseColor(0.6f, 0.6f, 0.6f, 1.0f),  
    specularColor(1.0f, 1.0f, 1.0f, 1.0f), 
    shinnines(16.0f)                        
{}

Material::Material(const glm::vec4& ambient,
    const glm::vec4& diffuse,
    const glm::vec4& specular,
    const float shin)
    : ambientColor(ambient),
    diffuseColor(diffuse),
    specularColor(specular),
    shinnines(shin)
{}

const glm::vec4& Material::getAmbientColor() const { return ambientColor; }
const glm::vec4& Material::getDiffuseColor() const { return diffuseColor; }
const glm::vec4& Material::getSpecularColor() const { return specularColor; }
const float Material::getShinnines() const { return shinnines; }

void Material::setAmbientColor(const glm::vec4& v) { ambientColor = v; }
void Material::setDiffuseColor(const glm::vec4& v) { diffuseColor = v; }
void Material::setSpecularColor(const glm::vec4& v) { specularColor = v; }
void Material::setShinnines(const float v) { shinnines = v; }

