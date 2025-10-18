#pragma once
#include "glm/glm.hpp"
#include <string>
class Observer {
public:
	virtual ~Observer() = default; ;
	virtual void Notify(const glm::mat4& view, const glm::mat4& projection) {};
	virtual void Notify(const glm::vec3& vector, std::string type) {};
	virtual void Notify(const glm::vec3& position, const glm::vec4& color, float intesnity, float shiness) {};

};