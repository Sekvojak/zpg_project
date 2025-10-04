#include "SceneManager.h"

void SceneManager::addScene(Scene* scene) {
	scenes.push_back(scene);
}

void SceneManager::setActiveScene(int index) {
	if (index >= 0 && index < (int)scenes.size())
	{
		activeSceneIndex = index;
	}
}

void SceneManager::drawActiveScene() {
	if (!scenes.empty())
	{
		scenes[activeSceneIndex]->draw();
	}
}

void SceneManager::updateActiveScene(float deltaTime) {
	if (!scenes.empty())
	{
		scenes[activeSceneIndex]->update(deltaTime);
	}
}

SceneManager::~SceneManager() {
	for (auto* scene : scenes) {
		delete scene;
	}
}