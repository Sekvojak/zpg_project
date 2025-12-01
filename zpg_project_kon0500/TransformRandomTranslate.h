#pragma once
#pragma once
#include "AbstractTransformation.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>

class TransformRandomTranslate : public AbstractTransformation
{
private:
	glm::vec3 position;
	glm::vec3 velocity;
	float changeInterval;
	float timeSinceChange;
public:
	TransformRandomTranslate(const glm::vec3& start = glm::vec3(0.0f), float interval = 5.0f) { 
		position = start;
		velocity = randomVelocity();
		changeInterval = interval;
		timeSinceChange = 0.0f;
	}

	void update(float deltaTime) override {
		timeSinceChange += deltaTime;

		if (timeSinceChange >= changeInterval)
		{
			velocity = randomVelocity();
			timeSinceChange = 0.0f;
		}

		position += velocity * deltaTime;
	}

	glm::vec3 randomVelocity() const {
		return glm::vec3(
			-15.0f + static_cast<float>(rand()) / RAND_MAX * 30.0f,
			-0.8f + static_cast<float>(rand()) / RAND_MAX * 1.6f,
			-13.0f + static_cast<float>(rand()) / RAND_MAX * 26.0f
		);
	}

	glm::mat4 getMatrix() const override {
		glm::mat4 result(1.0f);
		return glm::translate(result, position);
	}


};

