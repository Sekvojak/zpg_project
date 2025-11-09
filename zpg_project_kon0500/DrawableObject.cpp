#include <iostream>
#include "DrawableObject.h"


DrawableObject::DrawableObject(Model* model, ShaderProgram* shader, AbstractTransformation* transformation) {
	this->model = model;
	this->shader = shader;
	this->transformation = transformation;
}


void DrawableObject::draw() {
	shader->use();
	shader->setUniform("objectColor", objectColor);
	shader->setUniform("material.ra", material.ra);
	shader->setUniform("material.rd", material.rd);
	shader->setUniform("material.rs", material.rs);
	shader->setUniform("material.h", material.h);
	if (transformation) {
		shader->setUniform("modelMatrix", transformation->getMatrix());
	}
	else {
		shader->setUniform("modelMatrix", glm::mat4(1.0f)); // jednotková matica
	}

	if (material.texture) {
		material.texture->bind(GL_TEXTURE0);               
		shader->setUniform("hasTexture", 1);     
		shader->setUniform("texture1", 0);       
	}
	else {
		shader->setUniform("hasTexture", 0);
	}



	model->bind();
	glUseProgram(0);
}

AbstractTransformation* DrawableObject::getTransformation() {
	return transformation;
}

DrawableObject::~DrawableObject() {
	delete transformation;
}

void DrawableObject::setColor(const glm::vec3& color) {
	objectColor = color;
}

void DrawableObject::setTexture(Texture* tex) {
	material.texture = tex;
}