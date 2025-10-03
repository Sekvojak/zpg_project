#pragma once
#include "AbstractTransformation.h"

class TransformTranslate : public AbstractTransformation {
private:
	glm::vec3 translation;
public:
	TransformTranslate(const glm::vec3& translation) {
		this->translation = translation;
	}

	glm::mat4 getMatrix() const override {
		glm::mat4 result(1.0f);
		return glm::translate(result, translation);
	}


};

