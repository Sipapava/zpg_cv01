#pragma once
#include "model.h"
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

class ModelManager
{
private:
	std::vector<Model*> models;

public:
	ModelManager() = default;
	~ModelManager();

	Model* CreateModel(const Vertex* vertices, size_t count, const std::string& type, const std::string& name);
	Model* GetModelByName(const std::string& name) const;

	std::vector<Vertex> LoadModelFromObjectFile(const char* path);
	void createModelsForScenes();
	std::vector<Vertex> FromFloat(const float* data, size_t size, bool hasTexture, bool hasNormal);


};
