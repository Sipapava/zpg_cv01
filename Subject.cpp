#include "Subject.h"

void Subject::AddObserver(Observer* o) {
	observers.push_back(o);
}

void Subject::RemoveObserver(Observer* o) {
	observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
}

void Subject::NotifyObservers(const glm::mat4& matrix1, const glm::mat4& matrix2) {
	for (Observer* o : observers) {
		o->Notify(matrix1, matrix2);
	}
}

void Subject::NotifyObservers(const glm::vec3& position, const glm::vec4& color, float intesnity, float shiness) {
	for (Observer* o : observers) {
		o->Notify(position, color,intesnity,shiness);
	}
}

void Subject::NotifyObservers(const glm::vec3& vector, std::string type) {
	for (Observer* o : observers) {

		o->Notify(vector,type);
	}
}