#pragma once
#include "AbstractTransformation.h"

class TransformDynamicRotate : public AbstractTransformation{
private:
	float angle;
	float increment;
	glm::vec3 axis;

public:
	TransformDynamicRotate(float increment, const glm::vec3& axis) {
		this->increment = increment;    // speed of rotation
		this->axis = axis;
		this->angle = 0.0f;    // currentAngle
	}


	void update(float deltaTime) override {
		angle += increment * deltaTime;
	}

	glm::mat4 getMatrix() const override {
		glm::mat4 result(1.0f);
		return glm::rotate(result, glm::radians(angle), axis);
	}


};

