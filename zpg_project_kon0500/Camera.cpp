#include "Camera.h"
#include <algorithm>
#include <stdio.h>
#include <iostream> 


Camera::Camera(glm::vec3 eye, glm::vec3 up, float fieldOfView, int windowWidth, int windowHeight) {
	this->eye = eye;
	this->up = up;
	this->fieldOfView = fieldOfView;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	zNear = 0.1f;
	zFar = 100.0f;
	front = glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f));
	setViewport(windowWidth, windowHeight);

	updateView();
}

void Camera::setViewport(int width, int height) {
	this->windowHeight = height;
	this->windowWidth = width;

	glViewport(0, 0, windowWidth, windowHeight);
	updateProjection();
}

void Camera::setProjection(float fieldOfView) {
	this->fieldOfView = fieldOfView;
	updateProjection();
}

void Camera::setEyeFrontUp(glm::vec3 eye_, glm::vec3 front_, glm::vec3 up_) {
	eye = eye_;
	front = glm::normalize(front_);
	up = glm::normalize(up_);
	updateView();
}

void Camera::updateView() {
	viewMatrix = glm::lookAt(eye, eye + front, up);
	notifyObservers();
	// std::cout << "Eye: " << eye.x << ", " << eye.y << ", " << eye.z << std::endl;
	// std::cout << "Front: " << front.x << ", " << front.y << ", " << front.z << std::endl;
	// std::cout << "Up: " << up.x << ", " << up.y << ", " << up.z << std::endl;

}

void Camera::updateProjection() {
	float aspect = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
	projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspect, zNear, zFar);
	notifyObservers();
}

void Camera::attachObserver(ICameraObserver* observer) {
	observers.push_back(observer);
	if (observer) {
		observer->onCameraChanged(viewMatrix, projectionMatrix);
	}
}

void Camera::detachObserver(ICameraObserver* observer) {
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Camera::notifyObservers() {
	for (auto* o : observers) {
		o->onCameraChanged(viewMatrix, projectionMatrix);
	}
}