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

	// float randomFloat = MIN + static_cast<float>(rand()) / RAND_MAX * (MAX - MIN);

	
	for (int i = 0; i < 75; i++)
	{	
		auto* transform = new TransformationComposite();

		float s = 0.2f + static_cast<float>(rand()) / RAND_MAX * 0.2f; // random scale
		float x = -50.0f + static_cast<float>(rand()) / RAND_MAX * 100.0f; 
		float z = -25.0f + static_cast<float>(rand()) / RAND_MAX * 50.0f; 
		transform->addChild(new TransformScale(glm::vec3(s)));
		transform->addChild(new TransformTranslate(glm::vec3(x, 0.0f, z)));

		auto* obj = new DrawableObject(treeModel, shaderManager->get("basic"), transform);
		scene->addObject(obj);
	}

	for (int i = 0; i < 75; i++)
	{
		auto* transform = new TransformationComposite();

		float s = 1.5f + static_cast<float>(rand()) / RAND_MAX * 1.5f; 
		float x = -10.0f + static_cast<float>(rand()) / RAND_MAX * 20.0f; 
		float z = -5.0f + static_cast<float>(rand()) / RAND_MAX * 10.0f; 
		transform->addChild(new TransformScale(glm::vec3(s)));
		transform->addChild(new TransformTranslate(glm::vec3(x, 0.0f, z)));

		auto* obj = new DrawableObject(bushModel, shaderManager->get("sphere"), transform);
		scene->addObject(obj);
	}
	
	return scene;
}