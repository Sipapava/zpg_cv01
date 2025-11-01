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
	//glm::vec3 defaultPosition;
	//glm::vec3 positionSend;
	
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


//baterka podedi ze svetla a bude osberver camery
//rozsirit strukturu svetla v shaderu a podle typu Int taham co potrebuju
//pocitani do bufferu a az pak se spocita jedno osvetleni
//shdeProgram potom casem soupneme do materialu, coz jsou vlastne jen nastaveni shaderu
//bacha jeden model vlastne muze mit vice textur treba kmen a listy u stromu
//scena muze mit i manazer svetel at se o to nemusi starat