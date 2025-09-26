#include "ShaderProgram.h" 
#include <iostream> 

ShaderProgram::ShaderProgram(const char* vertexSrc, const char* fragmentSrc) {

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

	GLint status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	} 
} 

void ShaderProgram::use() {
	glUseProgram(shaderProgram); 
}