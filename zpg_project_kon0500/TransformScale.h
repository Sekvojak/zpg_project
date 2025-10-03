#pragma once
#include "AbstractTransformation.h"

class TransformScale : public AbstractTransformation{
private:
	glm::vec3 factor;

public:
	TransformScale(const glm::vec3& factor) {
		this->factor = factor;
	}
	glm::mat4 getMatrix() const override {
		glm::mat4 result(1.0f);
		return glm::scale(result, factor);
	}

};

