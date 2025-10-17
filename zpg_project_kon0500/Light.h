#pragma once
#include <glm/glm.hpp>
#include "ILightObserver.h"
#include <vector>

class Light
{
private:
	glm::vec3 position;
	glm::vec3 lightColor;

	std::vector<ILightObserver*> observers;
public:
	Light(glm::vec3 pos, glm::vec3 color);

	void attachObserver(ILightObserver* observer);
	void detachObserver(ILightObserver* observer);

	void setPosition(const glm::vec3& p);
	void setColor(const glm::vec3& c);

	void notifyObservers();


};

