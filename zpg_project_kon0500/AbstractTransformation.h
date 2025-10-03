#pragma once
#include <glm/gtc/matrix_transform.hpp>

class AbstractTransformation
{
public:
	virtual void update(float deltaTime) {}
	virtual glm::mat4 getMatrix() const = 0;
	virtual ~AbstractTransformation() {}

};