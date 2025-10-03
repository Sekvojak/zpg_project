#pragma once
#include "AbstractTransformation.h"

class TransformDynamicTranslate : public AbstractTransformation {
private:
	glm::vec3 velocity;
	glm::vec3 position;
public:

	TransformDynamicTranslate(const glm::vec3& velocity, const glm::vec3& start = glm::vec3(0.0f)) {
		this->velocity = velocity;
		this->position = start;
	}

	void update(float deltaTime) override {
		position += velocity * deltaTime;
	}

	glm::mat4 getMatrix() const override {
		glm::mat4 result(1.0f);
		return glm::translate(result, position);
	}


};

