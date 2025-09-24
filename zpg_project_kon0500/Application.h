#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "ShaderProgram.h"
#include "Mesh.h"


class Application
{
public:
	void initialization();
	void createShaders();
	void run();
	void createModels();

private:
	GLFWwindow* window = nullptr;
	std::unordered_map<std::string, Shader*> shaders;
	GLuint VAO, VBO;
	std::vector<Mesh*> meshes;
};

