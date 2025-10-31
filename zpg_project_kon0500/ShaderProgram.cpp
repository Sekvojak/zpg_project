#include "ShaderProgram.h" 
#include <iostream> 
#include <string>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Light.h"

ShaderProgram::ShaderProgram(const Shader& vertex, const Shader& fragment) {
	// shaderProgram setup
	camera = nullptr;
	lightManager = nullptr;
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
	glUseProgram(0);
}

void ShaderProgram::setLightManager(LightManager* lm) {
	if (this->lightManager)
		this->lightManager->detachObserver(this);
	this->lightManager = lm;
	if (lm)
		lm->attachObserver(this);
}

void ShaderProgram::onLightsChanged(const std::vector<Light*>& lights) {
	if (!shaderProgram) return;
	use();
	std::cout << "Updating lights: " << lights.size() << " for shader " << shaderProgram << "\n";
	setUniform("lightCount", (int)lights.size());
	for (int i = 0; i < lights.size(); i++) {
		setUniform("lights[" + std::to_string(i) + "].position", lights[i]->getPosition());
		setUniform("lights[" + std::to_string(i) + "].color", lights[i]->getColor());
		setUniform("lights[" + std::to_string(i) + "].direction", lights[i]->getDirection());
		setUniform("lights[" + std::to_string(i) + "].constant", lights[i]->getConstant());
		setUniform("lights[" + std::to_string(i) + "].linear", lights[i]->getLinear());
		setUniform("lights[" + std::to_string(i) + "].quadratic", lights[i]->getQuadratic());
		setUniform("lights[" + std::to_string(i) + "].cutOff", lights[i]->getCutOff());
		setUniform("lights[" + std::to_string(i) + "].type", (int)lights[i]->getType());
		setUniform("lights[" + std::to_string(i) + "].active", lights[i]->isActive());
	}
	glUseProgram(0);
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