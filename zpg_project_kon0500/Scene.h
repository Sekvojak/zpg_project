#pragma once
#include <vector>
#include "DrawableObject.h"
#include "LightManager.h"

#include "Skybox.h"

class Scene
{
private:
	std::vector<DrawableObject*> objects;
	LightManager* lightManager;		
	Skybox* skybox = nullptr;
public:
	~Scene();
	void addObject(DrawableObject* object);
	void draw();
	void update(float deltaTime); 
	void setLightManager(LightManager* lm);
	LightManager* getLightManager();
	void setSkybox(Skybox* sb) { skybox = sb; }
};

