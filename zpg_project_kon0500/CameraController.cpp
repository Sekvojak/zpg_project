#include "CameraController.h"
#include <glm/gtc/matrix_transform.hpp>

CameraController::CameraController(Camera* cam) {
	this->camera = cam;
	eye = glm::vec3(0.0f, 0.0f, 3.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	yaw = -90.0f;  // otacanie dolava / doprava -zacina -90 aby bol front do -z
	pitch = 0.0f;  // hore/dole uhol
	speed = 2.0f;   // rychlsot WASD
	sensitivity = 0.19f;   // rychlsot mysi
	firstMouseMove = true;


	camera->attachObserver(this);
	camera->setEyeFrontUp(eye, front, up);
}

void CameraController::onCameraChanged(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
	// 
}

void CameraController::update(GLFWwindow* window, float dt) {
	float velocity = speed * dt;
	glm::vec3 right = glm::normalize(glm::cross(front, up));

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		eye += front * velocity;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		eye -= front * velocity;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		eye -= right * velocity;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		eye += right * velocity;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		eye += up * velocity;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		eye -= up * velocity;
	}

	camera->setEyeFrontUp(eye, front, up);
}

void CameraController::processMouse(GLFWwindow* window) {

	double xPosition, yPosition;
	glfwGetCursorPos(window, &xPosition, &yPosition);

	if (firstMouseMove)
	{
		lastX = xPosition;
		lastY = yPosition;
		firstMouseMove = false;
	}

	float xOffset = (float)(xPosition - lastX) * sensitivity;
	float yOffset = (float)(lastY - yPosition) * sensitivity;
	lastX = xPosition;
	lastY = yPosition;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(direction);

	camera->setEyeFrontUp(eye, front, up);


}

void CameraController::checkResize(GLFWwindow* window) {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	static int lastWidth = width;
	static int lastHeight = height;

	if (width != lastWidth || height != lastHeight) {
		camera->setViewport(width, height);
		lastWidth = width;
		lastHeight = height;
	}
}