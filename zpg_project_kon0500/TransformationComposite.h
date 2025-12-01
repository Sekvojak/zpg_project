#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "AbstractTransformation.h"
#include "TransformTranslate.h"
#include "TransformBezierSpline.h"

class TransformationComposite : public AbstractTransformation{

private:
	std::vector<AbstractTransformation*> children; 

public:
	TransformationComposite () = default;
	~TransformationComposite() = default;

	void addChild(AbstractTransformation* t) {
		children.push_back(t);
	}

	void addChildAtBeginning(AbstractTransformation* t) {
		children.insert(children.begin(), t);
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

	bool removeAllTranslates()
	{
		bool removed = false;

		for (auto it = children.begin(); it != children.end(); )
		{
			TransformTranslate* tt = dynamic_cast<TransformTranslate*>(*it);
			if (tt)
			{
				it = children.erase(it);
				removed = true;
			}
			else {
				++it;
			}
		}

		return removed;
	}

	void removeAllBezierSplines()
	{
		for (auto it = children.begin(); it != children.end(); )
		{
			auto* spline = dynamic_cast<TransformBezierSpline*>(*it);
			if (spline)
			{
				it = children.erase(it);  
			}
			else {
				++it;
			}
		}
	}


};

