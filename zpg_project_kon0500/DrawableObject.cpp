#include <iostream>
#include "DrawableObject.h"


DrawableObject::DrawableObject(Model* model, ShaderProgram* shader, AbstractTransformation* transformation) {
	this->model = model;
	this->shader = shader;
	this->transformation = transformation;
}


void DrawableObject::draw() {
	shader->use();
	shader->setUniform("model", transformation->getMatrix());
	model->bind();
}

AbstractTransformation* DrawableObject::getTransformation() {
	return transformation;
}