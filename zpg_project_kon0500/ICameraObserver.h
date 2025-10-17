#pragma once
#include <glm/glm.hpp>

// rozhranie pre objekty, ktoré chcú reagovať na zmenu kamery (napr. shader)
class ICameraObserver
{
public:
	virtual ~ICameraObserver() = default;

	// táto metóda sa zavolá, keď sa kamera zmení
	virtual void onCameraChanged(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& eye) = 0;

};

