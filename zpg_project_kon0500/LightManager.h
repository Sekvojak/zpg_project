#pragma once
#include <vector>
#include "Light.h"
#include "ILightObserver.h"

class LightManager
{
private:
	std::vector<Light*> lights;
	std::vector<ILightObserver* > observers;

public:
	void addLight(Light* light);
	void attachObserver(ILightObserver* o);
	void detachObserver(ILightObserver* o);
	void notifyObservers();
	const std::vector<Light*>& getLights();



};
