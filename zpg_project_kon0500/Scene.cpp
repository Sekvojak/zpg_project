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

		if (object->getLinkedLight()) {
			glm::vec3 newPos = object->getTransformation()->getMatrix()[3]; 
			object->getLinkedLight()->setPosition(glm::vec3(newPos.x, newPos.y, newPos.z));
		}
	}

	if (lightManager)
		lightManager->notifyObservers();
}

LightManager* Scene::getLightManager() {
	return lightManager;
}

void Scene::setLightManager(LightManager* lm) {
	lightManager = lm;
}

Scene::~Scene() {
	for (auto* object : objects) {
		delete object;
	}
}

