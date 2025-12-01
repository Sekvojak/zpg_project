#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "ICameraObserver.h"

class Camera
{
private:
	// position and orientation
	glm::vec3 eye; 
	glm::vec3 front; 
	glm::vec3 up;

	// projection
	float fieldOfView;
	float zNear; 
	float zFar;  

	// viewport;
	int windowWidth;
	int windowHeight;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	std::vector<ICameraObserver*> observers;

	void updateView();
	void updateProjection();
	void notifyObservers();


public:
	Camera(glm::vec3 eye, glm::vec3 up, float fieldOfView, int windowWidth, int windowHeight);

	void setViewport(int width, int height); 
	 
	void setProjection(float fieldOfView); 

	void setEyeFrontUp(glm::vec3 eye_, glm::vec3 front_, glm::vec3 up_); 

	const glm::mat4 getViewMatrix() const {
		return viewMatrix;
	};

	const glm::mat4 getProjectionMatrix() const {
		return projectionMatrix;
	}

	void attachObserver(ICameraObserver* observer);
	void detachObserver(ICameraObserver* observer);

	int getWidth() const { return windowWidth; }
	int getHeight() const { return windowHeight; }

};

