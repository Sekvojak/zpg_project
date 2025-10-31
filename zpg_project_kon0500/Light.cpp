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

Light::Light(glm::vec3 vector, glm::vec3 color, LightType t) {
	this->lightColor = color;
	this->type = t;
	if (t == LightType::Directional)
	{
		this->direction = glm::normalize(vector);
	}
	else {
		this->position = vector;
	}
}

Light::Light(glm::vec3 pos, glm::vec3 color, LightType t, float c, float l, float q, float cut) {
	this->position = pos; this->lightColor = color; this->type = t;
	this->constant = c; this->linear = l; this->quadratic = q;
	this->cutOff = cut;
}



void Light::setColor(const glm::vec3& c) { lightColor = c; }

void Light::setPosition(const glm::vec3& p) { position = p; }

void Light::setDirection(const glm::vec3& d) { direction = glm::normalize(d); }

void Light::setAttenuation(float c, float l, float q) {
	constant = c; 
	linear = l;
	quadratic = q;
}

void Light::setCutOff(float c) { cutOff = c; }

void Light::setType(LightType t) { type = t; }

void Light::setActive(bool a) { active = a; }

const glm::vec3& Light::getPosition() const { return position; }
const glm::vec3& Light::getColor() const { return lightColor; }
const glm::vec3& Light::getDirection() const { return direction; }
LightType Light::getType() const { return type; }
bool Light::isActive() const { return active; }
float Light::getConstant() const { return constant; }
float Light::getLinear() const { return linear; }
float Light::getQuadratic() const { return quadratic; }
float Light::getCutOff() const { return cutOff; }