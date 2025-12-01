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

#include <vector>
#include "TransformBezierSpline.h"
#include "DrawableObject.h"

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

	bool bezierMode = false;
	std::vector<glm::vec3> bezierPoints;
	float bezierSpeed = 0.1f;
	std::vector<DrawableObject*> bezierMarkers;

};

