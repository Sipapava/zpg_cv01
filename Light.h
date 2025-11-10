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
	
	
	glm::vec4 colorSpecular;
	float specularIntesity;
	float shiness;
	glm::vec4 diffuseColor;
	
	

public:

	Light(const glm::vec4& colorSpecular, float intesnity, float shiness, const glm::vec4& colorDiffuse);
	Light(Model* m, ShaderProgram* sp,const glm::vec4& colorSpecular, float intesnity, float shiness, const glm::vec4& colorDiffuse);
	~Light() {};
	
	void UpdateLightsShaderPro();
	void AddObserver(Observer* o) override;
	void RemoveObserver(Observer* o) override;
	virtual LightData getLightData() const;
	virtual void Update();
	

	

};


