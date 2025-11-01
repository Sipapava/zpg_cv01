#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/epsilon.hpp>
#include "Subject.h"
#include "transformation.h"
#include "elementarTransformation.h"
#include "complexTransformation.h"
#include <iostream>

class Light : public Subject {
private:
	glm::vec3 defaultPosition;
	glm::vec3 positionSend;
	Transformation* transformation;
	glm::vec4 colorSpecular;
	float specularIntesity;
	float shiness;
	glm::vec4 diffuseColor;
	glm::vec4 ambientColor;
	float attenuation;

	int id;
	static int nextId;

public:

	Light(const glm::vec3& position, const glm::vec4& colorSpecular, float intesnity, float shiness, const glm::vec4& colorDiffuse, float attenuation, const glm::vec4& ambientColo);
	~Light() {};
	int GetId() const { return id; }
	void UpdateLightsShaderPro();
	void AddObserver(Observer* o) override;
	void RemoveObserver(Observer* o) override;
	LightData getLightData() const;
	void Update();
	void MoveTo(float x, float y, float z); // z techto metod  trida
	void Rotate(float angle, float xA, float yA, float zA);
	void SetRotateAnimation(float addAngle, const glm::vec3& axis);

	

};


//baterka podedi ze svetla a bude osberver camery
//rozsirit strukturu svetla v shaderu a podle typu Int taham co potrebuju
//pocitani do bufferu a az pak se spocita jedno osvetleni
//shdeProgram potom casem soupneme do materialu, coz jsou vlastne jen nastaveni shaderu
//bacha jeden model vlastne muze mit vice textur treba kmen a listy u stromu
//scena muze mit i manazer svetel at se o to nemusi starat