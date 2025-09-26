#include <iostream>
#include "Model.h"

Model::Model(Mesh* mesh, ShaderProgram* shader) : mesh(mesh), shader(shader) {}

void Model::draw() {
	shader->use();
	mesh->draw();
}