#pragma once
#include "AbstractTransformation.h"
#include <glm/glm.hpp>

class TransformBezier : public AbstractTransformation
{
private:
	glm::vec3 P0, P1, P2, P3;
	float t = 0.0f;
	float speed;

	glm::vec3 evaluateBezier(float t) const {
		float u = 1.0f - t;
		float u2 = u * u;
		float u3 = u2 * u;
		float t2 = t * t;
		float t3 = t2 * t;

		return
			u3 * P0 +
			3.0f * u2 * t * P1 +
			3.0f * u * t2 * P2 +
			t3 * P3;
	}

public:
	TransformBezier(
		const glm::vec3 p0,
		const glm::vec3 p1,
		const glm::vec3 p2,
		const glm::vec3 p3,
		float speed
	) {
		this->P0 = p0;
		this->P1 = p1;
		this->P2 = p2;
		this->P3 = p3;
		this->speed = speed;
	}

	void update(float dt) override {
		t += speed * dt;

		if (t > 1.0f)
		{
			t = 1.0f;
		}
	}

	bool finished() const {
		if (t >= 1.0f)
		{
			return true;
		}
		return false;
	}

	glm::mat4 getMatrix() const override {
		glm::vec3 position = evaluateBezier(t);
		return glm::translate(glm::mat4(1.0f), position);
	}



};

