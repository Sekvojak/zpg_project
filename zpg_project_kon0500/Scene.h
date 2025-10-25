#pragma once
#include <vector>
#include "DrawableObject.h"
#include "LightManager.h"


class Scene
{
private:
	std::vector<DrawableObject*> objects;
	LightManager* lightManager;
public:
	~Scene();
	void addObject(DrawableObject* object);
	void draw();
	void update(float deltaTime); 
	void setLightManager(LightManager* lm);
	LightManager* getLightManager();
};

