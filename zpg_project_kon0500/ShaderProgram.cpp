#include "ShaderProgram.h" 
#include <iostream> 
#include <string>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Light.h"

ShaderProgram::ShaderProgram(const Shader& vertex, const Shader& fragment) {
	// shaderProgram setup
	camera = nullptr;
	light = nullptr;
	shaderProgram = glCreateProgram(); 
	vertex.attachTo(shaderProgram);
	fragment.attachTo(shaderProgram);
	glLinkProgram(shaderProgram);

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

void ShaderProgram::setCamera(Camera* cam) {
	camera = cam;
	if (camera)
	{
		camera->attachObserver(this);
	}
}

void ShaderProgram::onCameraChanged(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& eye) {
	if (!shaderProgram) return;
	use();
	setUniform("viewMatrix", viewMatrix);
	setUniform("projectionMatrix", projectionMatrix);
	setUniform("viewPosition", eye);
}

void ShaderProgram::setLight(Light* l) {

	light = l;
	if (light)
	{
		light->attachObserver(this);
	}
}

void ShaderProgram::onLightChanged(const glm::vec3& position, const glm::vec3& color) {
	if (!shaderProgram) return;
	use();
	std::cout << "Light update: (" << position.x << "," << position.y << "," << position.z
		<< ") color=(" << color.r << "," << color.g << "," << color.b << ")\n";
	setUniform("lightPosition", position);
	setUniform("lightColor", color);
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