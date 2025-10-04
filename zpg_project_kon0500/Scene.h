#pragma once
#include <vector>
#include "DrawableObject.h"

class Scene
{
private:
	std::vector<DrawableObject*> objects;
public:
	~Scene();
	void addObject(DrawableObject* object);
	void draw();
	void update(float deltaTime); 
};

