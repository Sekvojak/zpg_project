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

class Application
{
public:
	void initialization();
	void createShaders();
	void run();
	void handleInput();
	void checkResize();
private:
	GLFWwindow* window = nullptr;
	ShaderManager shaderManager;
	SceneManager sceneManager;
	Camera* camera;
	CameraController* cameraController;
};

