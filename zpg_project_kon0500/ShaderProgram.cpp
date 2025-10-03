#include "ShaderProgram.h" 
#include <iostream> 
#include <string>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(const char* vertexSrc, const char* fragmentSrc) {

	// vertexShader setup
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); 
	glShaderSource(vertexShader, 1, &vertexSrc, nullptr); 
	glCompileShader(vertexShader); 
	
	// fragmentShader setup
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); 
	glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr); 
	glCompileShader(fragmentShader); 
	
	// shaderProgram setup
	shaderProgram = glCreateProgram(); 
	glAttachShader(shaderProgram, vertexShader); 
	glAttachShader(shaderProgram, fragmentShader); 
	glLinkProgram(shaderProgram); glDeleteShader(vertexShader); 
	glDeleteShader(fragmentShader); 

	// kontrola po linkovani shader programu
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
		exit(EXIT_FAILURE);
	} 
} 

ShaderProgram::~ShaderProgram() {
	if (shaderProgram)
	{
		glDeleteProgram(shaderProgram);
	}
}

void ShaderProgram::setUniform(const std::string& name, float value) {
	GLint loc = glGetUniformLocation(shaderProgram, name.c_str());
	if (loc != -1)
	{
		glUniform1f(loc, value);
	}
}
void ShaderProgram::setUniform(const std::string& name, int value) {
	GLint loc = glGetUniformLocation(shaderProgram, name.c_str());
	if (loc != -1)
	{
		glUniform1i(loc, value);
	}
}
void ShaderProgram::setUniform(const std::string& name, const glm::vec3& value) {
	GLint loc = glGetUniformLocation(shaderProgram, name.c_str());
	if (loc != -1)
	{
		glUniform3fv(loc, 1, glm::value_ptr(value));
	}
}
void ShaderProgram::setUniform(const std::string& name, const glm::mat4& value) {
	GLint loc = glGetUniformLocation(shaderProgram, name.c_str());
	if (loc != -1)
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
	}
}

void ShaderProgram::use() {
	glUseProgram(shaderProgram); 
}