#include "modelManager.h"
#include <algorithm>

ModelManager::~ModelManager()
{
	for (Model* m : models) {
		delete m;
	}
	models.clear();
}

Model* ModelManager::CreateModel(const Vertex* vertices, size_t count, const std::string& type, const std::string& name)
{
	Model* newModel = new Model(vertices, count, type, name);
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
