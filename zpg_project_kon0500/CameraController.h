#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Camera.h"
#include "ICameraObserver.h"

class CameraController : public ICameraObserver {

private:
	Camera* camera;
	
	glm::vec3 eye; // aktualna pozicia kamery pri otacani mysou napr
	glm::vec3 front; // smer pohladu
	glm::vec3 up; // vektor hore

	float yaw;
	float pitch;
	float speed;
	float sensitivity;

	bool firstMouseMove;
	double lastX, lastY;

public:
	CameraController(Camera* cam);

	// cita vstup, meni poziciu kamery
	void update(GLFWwindow* window, float dt);

	// spracuje mys
	void processMouse(GLFWwindow* window);

	void onCameraChanged(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

};

