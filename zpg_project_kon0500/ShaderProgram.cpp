#include "ShaderProgram.h" 
#include <iostream> 

Shader::Shader(const char* vertexSrc, const char* fragmentSrc) { 

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); 
	glShaderSource(vertexShader, 1, &vertexSrc, nullptr); 
	glCompileShader(vertexShader); 
	
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); 
	glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr); 
	glCompileShader(fragmentShader); 
	
	shaderProgram = glCreateProgram(); 
	glAttachShader(shaderProgram, vertexShader); 
	glAttachShader(shaderProgram, fragmentShader); 
	glLinkProgram(shaderProgram); glDeleteShader(vertexShader); 
	glDeleteShader(fragmentShader); 
} 

void Shader::use() { 
	glUseProgram(shaderProgram); 
}