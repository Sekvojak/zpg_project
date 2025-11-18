#include "Scene.h"
#include "SceneFactory.h"
#include "TransformationComposite.h"
#include "TransformTranslate.h"

void Scene::addObject(DrawableObject* object) {
	object->setID(this->nextObjectID++);
	objects.push_back(object);
}

void Scene::draw() {
	if (skybox) {
        glDisable(GL_STENCIL_TEST);
        skybox->draw();
    }
	

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	for (auto* object : objects) {
		glStencilFunc(GL_ALWAYS, object->getID(), 0xFF);

		object->setSelected(object->getID() == selectedObjectID);
		object->draw();
	}
}

void Scene::update(float deltaTime) {
	for (auto* object : objects) {
		if (object->getTransformation())
		{
			object->getTransformation()->update(deltaTime);
		}

		if (object->getLinkedLight()) {
			glm::vec3 newPos = object->getTransformation()->getMatrix()[3]; 
			object->getLinkedLight()->setPosition(glm::vec3(newPos.x, newPos.y, newPos.z));
		}
	}

	if (lightManager)
		lightManager->notifyObservers();
}

LightManager* Scene::getLightManager() {
	return lightManager;
}

void Scene::setLightManager(LightManager* lm) {
	lightManager = lm;
}

Scene::~Scene() {
	for (auto* object : objects) {
		delete object;
	}
}

void Scene::onClick(double x, double y, Camera* camera) {
	int winX = (int)x;
	int winY = camera->getHeight() - int(y) - 1;

	GLuint stencilIndex = 0;
	glReadPixels(winX, winY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &stencilIndex);

	std::cout << "Selected stencil ID: " << stencilIndex << std::endl;
	selectedObjectID = stencilIndex;

	float depth = 0.0f;
	glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

	std::cout << "Depth at click: " << depth << std::endl;

	glm::vec3 screenPos((float)winX, (float)winY, depth);
	glm::vec4 viewport(0, 0, camera->getWidth(), camera->getHeight());

	glm::vec3 worldPos = glm::unProject(screenPos, camera->getViewMatrix(), camera->getProjectionMatrix(), viewport);
	std::cout << "worldPos = ["
		<< worldPos.x << ", "
		<< worldPos.y << ", "
		<< worldPos.z << "]" << std::endl;

	lastWorldClickPosition = worldPos;
	hasWorldClick = true;
}

void Scene::deleteSelected() {
	if (selectedObjectID == 0)
	{
		return;
	}

	int indexToDelete = -1;

	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getID() == selectedObjectID) 
		{
			indexToDelete = i; 
			break;
		}
	}

	if (indexToDelete == -1)
	{
		return;
	}
	
	delete objects[indexToDelete];
	objects.erase(objects.begin() + indexToDelete);

	selectedObjectID = 0;
}

void Scene::plantTree(ModelManager* modelManager, ShaderManager* shaderManager) {
	if (!hasWorldClick)
	{
		return;
	}
	Model* treeModel = modelManager->get("tree");
	ShaderProgram* shaderLambert = shaderManager->clone("lambert");
	shaderLambert->setLightManager(this->lightManager);

	DrawableObject* newTree = SceneFactory::createTree(
		treeModel,
		shaderLambert,
		lastWorldClickPosition
	);

	addObject(newTree);

	std::cout << "Spawning tree at: "
		<< lastWorldClickPosition.x << ", "
		<< lastWorldClickPosition.y << ", "
		<< lastWorldClickPosition.z << std::endl;

	selectedObjectID = 0;


}

void Scene::moveSelected(float dx, float dy) {

	if (selectedObjectID == 0)
		return;

	for (auto* obj : objects) {
		if (obj->getID() == selectedObjectID)
		{
			obj->addOffset(glm::vec3(dx, 0.0f, dy));
			return;
		}
	}
}