#include "Scene.h"

Scene::Scene(ShaderProgram* shader)
    : shaderProgram(shader) {}

Scene::~Scene() {
    for (auto obj : drawableObjects) {
        delete obj;
    }
    drawableObjects.clear();
    // shaderProgram nema�eme, proto�e je vlastn�n mimo sc�nu
}

void Scene::addDrawableObject(DrawableObject* obj) {
    drawableObjects.push_back(obj);
}

void Scene::draw() {
    // Pokud by sc�na m�la pevn� dan� shader pro v�echny objekty:
    // if (shaderProgram) {
    //     shaderProgram->setShaderProgram();
    // }

    for (auto obj : drawableObjects) {
        obj->draw();
    }
}
