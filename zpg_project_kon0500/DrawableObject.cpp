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
	if (transformation) {
		shader->setUniform("modelMatrix", transformation->getMatrix());
	}
	else {
		shader->setUniform("modelMatrix", glm::mat4(1.0f)); // jednotková matica
	}
	model->bind();
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
