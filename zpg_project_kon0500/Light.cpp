#include "Light.h"

Light::Light(glm::vec3 pos, glm::vec3 color) {
	this->position = pos;
	this->lightColor = color;
	this->constant = 1.0f;
	this->linear = 0.0f;
	this->quadratic = 0.0f;
}

Light::Light(glm::vec3 pos, glm::vec3 color, float c, float l, float q) {
	this->position = pos;
	this->lightColor = color;
	setAttenuation(c, l, q);
}


void Light::setColor(const glm::vec3& c) {
	lightColor = c;
}

void Light::setPosition(const glm::vec3& p) {
	position = p;
}


void Light::setAttenuation(float c, float l, float q) {
	constant = c; 
	linear = l;
	quadratic = q;
}

