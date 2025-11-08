#pragma once
#include "drawableObject.h"
class drawableSky : public DrawableObject
{

public:
	drawableSky(Model* model,ShaderProgram* shader);
	void draw() override;
};

