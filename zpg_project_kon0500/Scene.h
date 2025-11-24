#pragma once
#include <vector>
#include "DrawableObject.h"
#include "LightManager.h"
#include "Camera.h"
#include "Skybox.h"
#include "ModelManager.h"
#include "ShaderManager.h"

class Scene
{
private:
	std::vector<DrawableObject*> objects;
	LightManager* lightManager;		
	Skybox* skybox = nullptr;

	int nextObjectID = 1;
	int selectedObjectID = -1;

	glm::vec3 lastWorldClickPosition = glm::vec3(0.0f);
	bool hasWorldClick = false;

public:
	~Scene();
	void addObject(DrawableObject* object);
	void removeObject(DrawableObject* object);
	void draw();
	void update(float deltaTime); 
	void setLightManager(LightManager* lm);
	LightManager* getLightManager();
	void setSkybox(Skybox* sb) { skybox = sb; }
	void onClick(double x, double y, Camera* camera);
	void deleteSelected();
	void plantTree(ModelManager* modelManager, ShaderManager* shaderManager);
	void moveSelected(float dx, float dz);

	DrawableObject* getObjectByID(int id);
	int getSelectedObjectID() const { return selectedObjectID; }
	std::vector<DrawableObject*>& getObjects() { return objects; }

};

