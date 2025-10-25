#include "LightManager.h"

void LightManager::addLight(Light* light) {
	lights.push_back(light);
	notifyObservers();
}

void LightManager::attachObserver(ILightObserver* o) {
	observers.push_back(o);
	o->onLightsChanged(lights);
}

void LightManager::detachObserver(ILightObserver* o) {
	observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
}

void LightManager::notifyObservers() {
	for (auto* o : observers) {
		o->onLightsChanged(lights);
	}
}

const std::vector<Light*>& LightManager::getLights() {
	return lights;
}