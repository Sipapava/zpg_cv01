#include "Scene.h"

Scene::Scene(ShaderProgram* shader)
    : shaderProgram(shader) {}

Scene::~Scene() {
    for (auto obj : drawableObjects) {
        delete obj;
    }
    drawableObjects.clear();
    // shaderProgram nemaeme, protoe je vlastnìn mimo scénu
}

void Scene::addDrawableObject(DrawableObject* obj) {
    drawableObjects.push_back(obj);
}

void Scene::draw() {
    // Pokud by scéna mìla pevnì danı shader pro všechny objekty:
    // if (shaderProgram) {
    //     shaderProgram->setShaderProgram();
    // }

    for (auto obj : drawableObjects) {
        obj->draw();
    }
}
