#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"
#include <iostream>

Texture::Texture(const std::string& filePath) {
	this->id = 0;
	this->width = 0;
	this->height = 0;
	this->channels = 0;
	this->filepath = filePath;


	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 4);
	if (!data) {
		std::cerr << "Failed to load texture: " << filePath << std::endl;
		return;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);	
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}


void Texture::bind(GLenum textureUnit) const {
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}