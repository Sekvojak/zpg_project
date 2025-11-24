#pragma once
#include "AbstractTransformation.h"

class TransformLinearParametric : public AbstractTransformation {
private:
	glm::vec3 A, B;
	float t = 0.0f;
	float speed;

public:
	TransformLinearParametric(glm::vec3 A, glm::vec3 B, float speed) {
		this->A = A;
		this->B = B;
		this->speed = speed;
	}

	void update(float dt) override {
		t += speed * dt;
		if (t > 1.0f)
		{
			t = 1.0f;
		}
	}

	bool finished() {
		if (t >= 1.0f)
		{
			return true;
		}
		return false;
	}

	glm::mat4 getMatrix() const override {
		glm::vec3 position = (1.0f - t) * A + t * B;
		return glm::translate(glm::mat4(1.0f), position);
	}


};

