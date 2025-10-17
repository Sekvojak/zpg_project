#include "Scene.h"

void Scene::addObject(DrawableObject* object) {
	objects.push_back(object);
}

void Scene::draw() {
	for (auto* object : objects) {
		object->draw();
	}
}

void Scene::update(float deltaTime) {
	for (auto* object : objects) {
		if (object->getTransformation())
		{
			object->getTransformation()->update(deltaTime);
		}
	}
}

Light* Scene::getLight() {
	return light;
}

void Scene::setLight(Light* l) { 
	light = l; 
}

Scene::~Scene() {
	for (auto* object : objects) {
		delete object;
	}
}

