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
	void AddObserver(Observer* o) override;
	void RemoveObserver(Observer* o) override;
	LightData getLightData() const;
	

};


//v shaderu s vice svetli pak slozky svetel jen secteme
//vzorec z phonga vyskyu=tuje se tam suma, umet ty matematicke zapisy
//koeficienty z toho vzorce se castou dodavaji do materialu se urcuji vlastnosti
// primarne implementace phonga nad vice svetly 
//utlum uvidime tak ze ten objekt/shader na kterem je nastaven nejde videt
//vic mensich jednodusich shaderu a prepinat mezi nimi