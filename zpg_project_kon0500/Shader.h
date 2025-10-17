#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <fstream>
#include <iostream>
#include <sstream>


class Shader {

private: 
	GLuint shaderId;

public:
	Shader() = default;
	Shader(GLenum type, const char* source);
	Shader(GLenum type, const std::string& shaderFile);
	~Shader();

	void createShader(GLenum type, const char* source);
	void createShaderFromFile(GLenum type, const std::string& shaderFile);

	void attachTo(GLuint shaderProgram) const;


};

