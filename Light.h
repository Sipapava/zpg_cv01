#pragma once
#include "drawableObject.h"
#include "subject.h"
#include "transformation.h"
#include "elementarTransformation.h"
#include "complexTransformation.h"
#include "glm/glm.hpp"

#include <iostream>

class Light : public subject, public DrawableObject {
protected:
	float specularIntesity;
public:

	Light(float intesnity);
	Light(Model* m, ShaderProgram* sp, float intesnity);
	~Light() {};
	
	void UpdateLightsShaderPro();
	void AddObserver(Observer* o) override;
	void RemoveObserver(Observer* o) override;
	virtual LightData getLightData() const;
	virtual void Update();
	

	

};


