#include "SceneFactory.h"
#include "DrawableObject.h"
#include "Model.h"
#include "TransformationComposite.h"
#include "TransformTranslate.h"
#include "TransformScale.h"
#include "TransformDynamicRotate.h"

#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/gift.h"
#include "Models/plain.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Models/sphere.h"

#include <cstdlib>   // rand()
#include <ctime>     // time()

Scene* SceneFactory::createScene1(ShaderManager* shaderManager) {
	// vertexy trojuholníka
	std::vector<float> triangle = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	Scene* scene = new Scene();
	Model* triangleModel = new Model(triangle, 3, 3, 0);
	triangleModel->setupMesh();

	auto* composite = new TransformationComposite();
	composite->addChild(new TransformDynamicRotate(90.0f, glm::vec3(0.0f, 0.0f, 1.0f)));
	auto* triangleObj = new DrawableObject(triangleModel, shaderManager->get("triangle"), composite);

	scene->addObject(triangleObj);

	return scene;
}


Scene* SceneFactory::createScene2(ShaderManager* shaderManager) {
	Scene* scene = new Scene();
	size_t sphereSize = sizeof(sphere) / sizeof(float);
	Model* sphereModel = new Model(std::vector<float>(sphere, sphere + sphereSize), 6, 3, 3);
	sphereModel->setupMesh();

	float scale = 0.2f;
	float translation = 2.5f;

	// -x gula
	auto* t1 = new TransformationComposite();
	t1->addChild(new TransformScale(glm::vec3(scale)));
	t1->addChild(new TransformTranslate(glm::vec3(-translation, 0.0f, 0.0f)));
	t1->addChild(new TransformDynamicRotate(45.0f, glm::vec3(0.0f, 0.0f, 1.0f)));
	auto* o1 = new DrawableObject(sphereModel, shaderManager->get("sphere"), t1);
	scene->addObject(o1);

	// x gula
	auto* t2 = new TransformationComposite();
	t2->addChild(new TransformScale(glm::vec3(scale)));
	t2->addChild(new TransformTranslate(glm::vec3(translation, 0.0f, 0.0f)));
	auto* o2 = new DrawableObject(sphereModel, shaderManager->get("sphere"), t2);
	scene->addObject(o2);

	// y gula
	auto* t3 = new TransformationComposite();
	t3->addChild(new TransformScale(glm::vec3(scale)));
	t3->addChild(new TransformTranslate(glm::vec3(0.0f, translation, 0.0f)));
	auto* o3 = new DrawableObject(sphereModel, shaderManager->get("sphere"), t3);
	scene->addObject(o3);

	// -y gula
	auto* t4 = new TransformationComposite();
	t4->addChild(new TransformScale(glm::vec3(scale)));
	t4->addChild(new TransformTranslate(glm::vec3(0.0f, -translation, 0.0f)));
	auto* o4 = new DrawableObject(sphereModel, shaderManager->get("sphere"), t4);
	scene->addObject(o4);

	return scene;
}

Scene* SceneFactory::createScene3(ShaderManager* shaderManager) {

	srand((unsigned)time(nullptr));
	auto* scene = new Scene();

	Model* treeModel = new Model(std::vector<float>(tree, tree + sizeof(tree) / sizeof(float)), 6, 3, 3);
	treeModel->setupMesh();

	Model* bushModel = new Model(std::vector<float>(bushes, bushes + sizeof(bushes) / sizeof(float)), 6, 3, 3);
	bushModel->setupMesh();

	Model* suziFlatModel = new Model(std::vector<float>(suziFlat, suziFlat + sizeof(suziFlat) / sizeof(float)), 6, 3, 3);
	suziFlatModel->setupMesh();

	Model* sphereModel = new Model(std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(float) ), 6, 3, 3);
	sphereModel->setupMesh();

	
	for (int i = 0; i < 5; i++)
	{	
		auto* transform = new TransformationComposite();

		float s = 0.05f + static_cast<float>(rand() % 10) / 2000.0f; // random scale
		float x = -10.0f + static_cast<float>(rand()) / RAND_MAX * 20.0f; // -10.0 .. +10.0
		float y = -5.0f + static_cast<float>(rand()) / RAND_MAX * 10.0f; // -5.0 .. +5.0
		transform->addChild(new TransformScale(glm::vec3(s)));
		transform->addChild(new TransformTranslate(glm::vec3(x, y, 0.0f)));

		auto* obj = new DrawableObject(treeModel, shaderManager->get("triangle"), transform);
		scene->addObject(obj);
	}

	for (int i = 0; i < 5; i++)
	{
		auto* transform = new TransformationComposite();

		float s = 0.3f + static_cast<float>(rand()) / RAND_MAX * (1.2f - 0.3f); // random scale
		float x = -1.0f + static_cast<float>(rand()) / RAND_MAX * (1.0f - -1.0f);
		transform->addChild(new TransformScale(glm::vec3(s)));
		transform->addChild(new TransformTranslate(glm::vec3(x, -0.5f, 0.0f)));

		auto* obj = new DrawableObject(bushModel, shaderManager->get("basic"), transform);
		scene->addObject(obj);
	}

	for (int i = 0; i < 5; i++)
	{
		auto* transform = new TransformationComposite();

		float s = 0.05f + static_cast<float>(rand()) / RAND_MAX * (0.1f - 0.05f); // random scale
		float x = -10.0f + static_cast<float>(rand()) / RAND_MAX * (10.0f - -10.0f);
		transform->addChild(new TransformScale(glm::vec3(s)));
		transform->addChild(new TransformTranslate(glm::vec3(x, 0.5f, 0.0f)));

		auto* obj = new DrawableObject(suziFlatModel, shaderManager->get("sphere"), transform);
		scene->addObject(obj);
	}

	for (int i = 0; i < 5; i++)
	{
		auto* transform = new TransformationComposite();

		float s = 0.1f + static_cast<float>(rand()) / RAND_MAX * (0.2f - 0.1f); // random scale
		float x = -5.0f + static_cast<float>(rand()) / RAND_MAX * (5.0f - -5.0f);
		transform->addChild(new TransformScale(glm::vec3(s)));
		transform->addChild(new TransformTranslate(glm::vec3(x, 2.8f, 0.0f)));

		auto* obj = new DrawableObject(sphereModel, shaderManager->get("sphere"), transform);
		scene->addObject(obj);
	}


	
	return scene;
}