#pragma once
#include <vector>
#include "DrawableObject.h"
#include "Light.h"


class Scene
{
private:
	std::vector<DrawableObject*> objects;
	Light* light;
public:
	~Scene();
	void addObject(DrawableObject* object);
	void draw();
	void update(float deltaTime); 
	void setLight(Light* l);
	Light* getLight();
};

