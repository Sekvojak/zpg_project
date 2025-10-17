#include "Shader.h"
#include <iostream>

void Shader::attachTo(GLuint shaderProgram) const {
	glAttachShader(shaderProgram, shaderId);
}

Shader::Shader(GLenum type, const char* source) {
	createShader(type, source);
}

Shader::Shader(GLenum shaderType, const std::string& shaderFile) {
	createShaderFromFile(shaderType, shaderFile);
}

void Shader::createShader(GLenum type, const char* source) {
	shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, &source, nullptr);


	glCompileShader(shaderId);

	GLint success;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
		std::cerr << "Shader compilation failed:\n" << infoLog << std::endl;
		exit(-1);
	}
}

void Shader::createShaderFromFile(GLenum type, const std::string& shaderFile) {

	std::ifstream file(shaderFile);
	if (!file.is_open()) {
		std::cerr << "Unable to open shader file: " << shaderFile << std::endl;
		exit(-1);
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string shaderCode = buffer.str();

	createShader(type, shaderCode.c_str());

}

Shader::~Shader() {
	if (shaderId != 0)
		glDeleteShader(shaderId);
}