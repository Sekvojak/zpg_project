#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>


class Shader {

private: 
	GLuint shaderId;

public:
	Shader(GLenum type, const char* source);
	~Shader();

	void attachTo(GLuint shaderProgram) const;


};

