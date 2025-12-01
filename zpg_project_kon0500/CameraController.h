#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Camera.h"
#include "ICameraObserver.h"
#include "Light.h"

class CameraController : public ICameraObserver {

private:
	Camera* camera;
	
	glm::vec3 eye; // current camera position
	glm::vec3 front; 
	glm::vec3 up; 

	float yaw;
	float pitch;
	float speed;
	float sensitivity;

	bool rightMouseHeld;
	double lastX, lastY;

	Light* flashlight;
	bool flashlightEnabled = true;

public:
	CameraController(Camera* cam);

	// change of camera position
	void update(GLFWwindow* window, float dt);

	// rotation of camera
	void processMouse(GLFWwindow* window);

	void onCameraChanged(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& eye);

	void checkResize(GLFWwindow* window);

	Light* getFlashlight() const { return flashlight; }

};

