#pragma once
#include <vector>
#include "Scene.h"

class SceneManager
{
private:
	std::vector<Scene*> scenes;
	int activeSceneIndex;
public:
	~SceneManager();
	void addScene(Scene* scene);
	void setActiveScene(int index);
	void drawActiveScene();
	void updateActiveScene(float deltaTime);
};

