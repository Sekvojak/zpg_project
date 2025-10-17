#include "Light.h"

Light::Light(glm::vec3 pos, glm::vec3 color) {
	this->position = pos;
	this->lightColor = color;

}

void Light::attachObserver(ILightObserver* observer) {
	observers.push_back(observer);
	observer->onLightChanged(position, lightColor);
}

void Light::detachObserver(ILightObserver* observer) {
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Light::notifyObservers() {
	for (auto* o : observers) {
		o->onLightChanged(position, lightColor);
	}
}

void Light::setColor(const glm::vec3& c) {
	lightColor = c;
	notifyObservers();
}

void Light::setPosition(const glm::vec3& p) {
	position = p;
	notifyObservers();
}

