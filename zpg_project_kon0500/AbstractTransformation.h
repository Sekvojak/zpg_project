#pragma once
#include <glm/gtc/matrix_transform.hpp>

// upadate nema zmysel?
// ked zavolam getMatrix tak sa privatne zavola update?


class AbstractTransformation
{
public:
	virtual void update(float deltaTime) {}
	virtual glm::mat4 getMatrix() const = 0;
	virtual ~AbstractTransformation() {}

};