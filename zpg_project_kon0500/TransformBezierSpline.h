#pragma once
#include "AbstractTransformation.h"
#include <glm/glm.hpp>
#include <vector>

class TransformBezierSpline : public AbstractTransformation
{
protected:
	std::vector<glm::vec3> points;
	float t = 0.0f;
	float speed;
	int segmentCount;

	glm::vec3 BezierPoint(
		const glm::vec3& P0,
		const glm::vec3& P1,
		const glm::vec3& P2,
		const glm::vec3& P3,
		float t) const 
	{
		float u = 1.0f - t;
		float u2 = u * u;
		float u3 = u2 * u;

		float t2 = t * t;
		float t3 = t2 * t;

		return u3 * P0
			+ 3.0f * u2 * t * P1
			+ 3.0f * u * t2 * P2
			+ t3 * P3;

	}

	glm::vec3 BezierDerivate(
		const glm::vec3& P0,
		const glm::vec3& P1,
		const glm::vec3& P2,
		const glm::vec3& P3,
		float t) const 
	{
		float u = 1.0f - t;
		glm::vec3 term1 = 3.0f * u * u * (P1 - P0);
		glm::vec3 term2 = 6.0f * u * t * (P2 - P1);
		glm::vec3 term3 = 3.0f * t * t * (P3 - P2);

		return term1 + term2 + term3;
	}


public:
	TransformBezierSpline(const std::vector<glm::vec3>& controlPoints, float speed) {
		this->points = controlPoints;
		this->speed = speed;

		if (points.size() >= 4)
		{
			segmentCount = (points.size() - 1) / 3;
		}
	}

	void update(float dt) override {
		t += speed * dt;

		if (t >= 1.0f)
		{
			t = 1.0f;
		}
	}

	glm::mat4 getMatrix() const override {

		if (segmentCount == 0)
		{
			return glm::mat4(1.0f);
		}

		float segmentLen = 1.0f / segmentCount;
		int segment = glm::min(int(t / segmentLen), segmentCount - 1); 
		float tLocal = (t - segment * segmentLen) / segmentLen; 

		int i = segment * 3; 

		glm::vec3 P0 = points[i];
		glm::vec3 P1 = points[i + 1];
		glm::vec3 P2 = points[i + 2];
		glm::vec3 P3 = points[i + 3];

		glm::vec3 position = BezierPoint(P0, P1, P2, P3, tLocal);
		
		glm::vec3 tangent = BezierDerivate(P0, P1, P2, P3, tLocal);
		tangent = glm::normalize(tangent);

		glm::vec3 forward = tangent;
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 right = glm::normalize(glm::cross(up, forward));
		glm::vec3 newUp = glm::cross(forward, right);

		glm::mat4 rotation(1.0f);
		rotation[0] = glm::vec4(right, 0.0f);
		rotation[1] = glm::vec4(newUp, 0.0f);
		rotation[2] = glm::vec4(forward, 0.0f);
		
		return glm::translate(glm::mat4(1.0f), position) * rotation;



	}


};

