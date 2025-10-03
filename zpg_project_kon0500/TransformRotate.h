#pragma once
#include "AbstractTransformation.h"

class TransformRotate : public AbstractTransformation{
private:
	float angle;
	glm::vec3 axis;
public:
	TransformRotate(float angle, const glm::vec3& axis) {
		this->angle = angle;
		this->axis = axis;
	}

	glm::mat4 getMatrix() const override {
		glm::mat4 result(1.0f);
		return glm::rotate(result, angle, axis);
	}


};

