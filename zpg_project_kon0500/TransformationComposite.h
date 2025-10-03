#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "AbstractTransformation.h"

class TransformationComposite : public AbstractTransformation{

private:
	std::vector<AbstractTransformation*> children; 

public:
	TransformationComposite () = default;
	~TransformationComposite() = default;

	void addChild(AbstractTransformation* t) {
		children.push_back(t);
	}

	void update(float deltaTime) override {
		for (auto c : children) {
			c->update(deltaTime);
		}
	}

	glm::mat4 getMatrix() const override {
		glm::mat4 result(1.0f);
		for (auto c : children) {
			result *= c->getMatrix();
		}
		return result;
	}

	void reset() {
		children.clear();
	}


};

