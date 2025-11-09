#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>


class Texture
{
private:
	GLuint id;
	int width; 
	int height; 
	int channels;
	std::string filepath;

public:
	Texture(const std::string& filePath);
	~Texture();

	void bind(GLenum textureUnit = GL_TEXTURE0) const;
	void unbind() const;

};

