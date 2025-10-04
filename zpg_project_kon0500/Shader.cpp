#include "Shader.h"
#include <iostream>

// pripojenie k shaderProgram
void Shader::attachTo(GLuint shaderProgram) const {
	glAttachShader(shaderProgram, shaderId);
}

Shader::Shader(GLenum type, const char* source) {
	shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, &source, nullptr);
	glCompileShader(shaderId);

	GLint success;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
		std::cerr << "Shader compilation failed:\n" << infoLog << std::endl;
	}
}

Shader::~Shader() {
	if (shaderId != 0)
		glDeleteShader(shaderId);
}