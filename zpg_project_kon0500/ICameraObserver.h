#pragma once
#include <glm/glm.hpp>

class ICameraObserver
{
public:
	virtual ~ICameraObserver() = default;

	virtual void onCameraChanged(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& eye) = 0;

};

