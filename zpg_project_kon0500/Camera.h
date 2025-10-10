#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "ICameraObserver.h"

class Camera
{
private:
	// pozicia a orientacia kamery
	glm::vec3 eye; // pozicia kamery
	glm::vec3 front; // smer kam sa kamera pozera
	glm::vec3 up;

	// parametre projekcie
	float fieldOfView;
	float zNear; // najbližšia rovina (zNear = 0.1)
	float zFar;  // najvzdialenejšia rovina (zFar = 100)

	// viewport;
	int windowWidth;
	int windowHeight;

	// Matice
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	std::vector<ICameraObserver*> observers;

	void updateView();
	void updateProjection();
	void notifyObservers();


public:
	Camera(glm::vec3 eye, glm::vec3 up, float fieldOfView, int windowWidth, int windowHeight);

	// viewport
	void setViewport(int width, int height); // nastaví viewport od (0,0) a aktualizuje aspect ratio
	 
	// projekcia
	void setProjection(float fieldOfView); // zmení zorné pole a obnoví projekciu

	// orientacia
	void setEyeFrontUp(glm::vec3 eye_, glm::vec3 front_, glm::vec3 up_); // nastaví polohu a orientáciu kamery

	const glm::mat4 getViewMatrix() const {
		return viewMatrix;
	};

	const glm::mat4 getProjectionMatrix() const {
		return projectionMatrix;
	}

	void attachObserver(ICameraObserver* observer);
	void detachObserver(ICameraObserver* observer);

};

