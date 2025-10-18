#pragma once
#include "glm/glm.hpp"
#include "Subject.h"

class Light : public Subject {
private:
	glm::vec3 position;
	glm::vec4 color;
	float specularIntesity;
	float shiness;

	int id;
	static int nextId;

public:

	Light(const glm::vec3& position, const glm::vec4& color, float intesnity,float shiness);
	~Light() {};
	int GetId() const { return id; }
	void UpdateLightsShaderPro();
	

};