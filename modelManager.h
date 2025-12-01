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

	Model* CreateModel(const float* data, size_t size, bool hasTexture, bool hasNormal, const std::string& type, const std::string& name);
	Model* CreateModel(const char* file, const std::string& type, const std::string& name);
	Model* GetModelByName(const std::string& name) const;

	
	void createModelsForScenes();
	


};
