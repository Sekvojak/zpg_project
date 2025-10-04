#include <iostream>
#include "DrawableObject.h"


DrawableObject::DrawableObject(Model* model, ShaderProgram* shader, AbstractTransformation* transformation) {
	this->model = model;
	this->shader = shader;
	this->transformation = transformation;
}


void DrawableObject::draw() {
	shader->use();
	if (transformation) {
		shader->setUniform("model", transformation->getMatrix());
	}
	else {
		shader->setUniform("model", glm::mat4(1.0f)); // jednotková matica
	}
	model->bind();
}

AbstractTransformation* DrawableObject::getTransformation() {
	return transformation;
}

DrawableObject::~DrawableObject() {
	delete transformation;
}
