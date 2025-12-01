#include "modelManager.h"
#include <algorithm>

#include "tree.h"
#include "skycube.h"
#include "bushes.h"
#include "sphere.h"

ModelManager::~ModelManager()
{
	for (Model* m : models) {
		delete m;
	}
	models.clear();
}

Model* ModelManager::CreateModel(const float* data, size_t size, bool hasTexture, bool hasNormal, const std::string& type, const std::string& name)
{
	Model* newModel = new Model(data,size,hasTexture,hasNormal, type, name);
	models.push_back(newModel);
	return newModel;
}

Model* ModelManager::CreateModel(const char* file, const std::string& type, const std::string& name)
{
    Model* newModel = new Model(file, type, name);
    models.push_back(newModel);
    return newModel;
}

Model* ModelManager::GetModelByName(const std::string& name) const
{
	for (Model* m : models) {
		if (m->getName() == name) {
			return m;
		}
	}
	return nullptr;
}


void ModelManager::createModelsForScenes() {

    const int sphereSize = sizeof(sphere) / sizeof(sphere[0]);
   

    std::vector<std::string> faces = {
    "skybox/posx.jpg",
    "skybox/negx.jpg",
    "skybox/posy.jpg",
    "skybox/negy.jpg",
    "skybox/posz.jpg",
    "skybox/negz.jpg"
    };

    const int cubeSize = sizeof(skycube) / sizeof(skycube[0]);
    this->CreateModel(skycube, cubeSize, false, false, "triangles", "skyCube");

    this->CreateModel(sphere, sphereSize, false, true, "triangles", "sphere");

    this->CreateModel("models/formula1.obj", "triangles", "formule");

    const float planeVertices[] = {
    -2.0f, -0.4f, 0.0f,   0.0f, 0.5f, 0.0f,   0.0f,   0.0f,
     2.0f, -0.4f, 0.0f,   0.0f, 0.5f, 0.0f,   100.0f, 0.0f,
     2.0f, -0.4f, 2.5f,   0.0f, 0.5f, 0.0f,   100.0f, 100.0f,

     2.0f, -0.4f, 2.5f,   0.0f, 0.5f, 0.0f,   100.0f, 100.0f,
    -2.0f, -0.4f, 2.5f,   0.0f, 0.5f, 0.0f,   0.0f,   100.0f,
    -2.0f, -0.4f, 0.0f,   0.0f, 0.5f, 0.0f,   0.0f,   0.0f
    };

    const int treeSize = sizeof(tree) / sizeof(tree[0]);
   
    const int bushSize = sizeof(bushes) / sizeof(bushes[0]);

    this->CreateModel(tree, treeSize, false, true, "triangles", "tree");

    this->CreateModel(bushes, bushSize, false, true, "triangles", "bush");

   
    this->CreateModel("models/skydome.obj", "triangles", "skyDom");

    this->CreateModel(planeVertices, sizeof(planeVertices) / sizeof(planeVertices[0]), true, true, "triangles", "plane");

    this->CreateModel("models/shrek.obj", "triangles", "shrek");

    this->CreateModel("models/fiona.obj", "triangles", "fiona");

    this->CreateModel("models/fatcat.obj", "triangles", "cat");
    
    this->CreateModel("models/spinosaurus.obj", "triangles", "spinosaurus");

    this->CreateModel("models/planet.obj", "triangles", "planet");

    this->CreateModel("models/login.obj", "triangles", "login");

}

