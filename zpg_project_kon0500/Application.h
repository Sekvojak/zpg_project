#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderProgram.h"
#include "Shader.h"
#include "SceneManager.h"
#include "SceneFactory.h"
#include "Camera.h"
#include "CameraController.h"
#include "ShaderManager.h"
#include "ModelManager.h"

#include "ShootingRange.h"

class Application
{
public:
	void initialization();
	void createShaders();
	void createModels();
	void run();
	void handleInput();
	void handleLeftClick();
	void setupScenes();
private:
	GLFWwindow* window = nullptr;
	ShaderManager shaderManager;
	ModelManager modelManager;
	SceneManager sceneManager;
	Camera* camera;
	CameraController* cameraController;

	ShootingRange* shooting = nullptr;
	bool shootingActive = false;
};

