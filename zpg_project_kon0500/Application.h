#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "ShaderProgram.h"
#include "Model.h"
#include "DrawableObject.h"


class Application
{
public:
	void initialization();
	void createShaders();
	void run();
	void createModels();

private:
	GLFWwindow* window = nullptr;
	std::unordered_map<std::string, ShaderProgram*> shaders;
	std::vector<Model*> models;
	std::vector<DrawableObject*> objects;
};

