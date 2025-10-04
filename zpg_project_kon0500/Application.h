#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include "ShaderProgram.h"
#include "Shader.h"
#include "SceneManager.h"
#include "SceneFactory.h"


class Application
{
public:
	void initialization();
	void createShaders();
	void run();
	void handleInput();
private:
	GLFWwindow* window = nullptr;
	std::map<std::string, ShaderProgram*> shaders;
	SceneManager sceneManager;
};

