#pragma once
#include "observer.h"
#include <vector>
#include "glm/glm.hpp"
#include <stdio.h>
#include <string>
class Subject {
protected:
	std::vector<Observer*> observers;
public:
	virtual ~Subject() = default; 
	virtual void AddObserver(Observer* o);
	virtual void RemoveObserver(Observer* o);
	virtual void NotifyObservers(const glm::mat4& matrix1, const glm::mat4& matrix2);
	virtual void NotifyObservers(const glm::vec3& vector, std::string type);
	virtual void NotifyObservers(const glm::vec3& position, const glm::vec4& color, float intesnity, float shiness);

};

//rotace udelat ttridu co dedi z rotate bude se to jmenvat treba rotace kolem obecneho bodu
//ta orovede translaci ritaci a translaci
//bude to tedz jeden objekt transformation