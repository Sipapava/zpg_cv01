#pragma once
#include "model.h"
#include <vector>
#include <string>

class ModelManager
{
private:
	std::vector<Model*> models;

public:
	ModelManager() = default;
	~ModelManager();

	Model* CreateModel(const Vertex* vertices, size_t count, const std::string& type, const std::string& name);
	Model* GetModelByName(const std::string& name) const;


};
