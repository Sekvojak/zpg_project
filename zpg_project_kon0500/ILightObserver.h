#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Light.h"

class Light;

class ILightObserver
{
public:
	virtual void onLightsChanged(const std::vector<Light*>& lights) = 0;
	~ILightObserver() = default;


};

