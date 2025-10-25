#include "SceneFactory.h"
#include "DrawableObject.h"
#include "Model.h"
#include "TransformationComposite.h"
#include "TransformTranslate.h"
#include "TransformScale.h"
#include "TransformDynamicRotate.h"
#include "TransformRandomTranslate.h"
#include "TransformRotate.h"


#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/gift.h"
#include "Models/plain.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Models/sphere.h"

#include <cstdlib>   // rand()
#include <ctime>     // time()

#include <glm/glm.hpp>

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
	auto* triangleObj = new DrawableObject(triangleModel, shaderManager->clone("constant"), composite);
	triangleObj->setColor(glm::vec3(1.0f, 1.0f, 0.0f));

	scene->addObject(triangleObj);

	return scene;
}


Scene* SceneFactory::createScene2(ShaderManager* shaderManager) {
	Scene* scene = new Scene();

	auto* lightManager = new LightManager();
	auto* light1 = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	lightManager->addLight(light1);

	auto* shaderConst = shaderManager->clone("constant");
	auto* shaderLambert = shaderManager->clone("lambert");
	auto* shaderPhong = shaderManager->clone("phong");
	auto* shaderBlinn = shaderManager->clone("blinn");

	lightManager->attachObserver(shaderLambert);
	lightManager->attachObserver(shaderPhong);
	lightManager->attachObserver(shaderBlinn);

	scene->setLightManager(lightManager);

	size_t sphereSize = sizeof(sphere) / sizeof(float);
	Model* sphereModel = new Model(std::vector<float>(sphere, sphere + sphereSize), 6, 3, 3);
	sphereModel->setupMesh();

	float scale = 0.2f;
	float translation = 2.5f;

	// -x gula
	auto* t1 = new TransformationComposite();
	t1->addChild(new TransformScale(glm::vec3(scale)));
	t1->addChild(new TransformTranslate(glm::vec3(-translation, 0.0f, 0.0f)));
	auto* o1 = new DrawableObject(sphereModel, shaderConst, t1);
	o1->setColor(glm::vec3(0.385, 0.647, 0.812));
	scene->addObject(o1);

	// x gula
	auto* t2 = new TransformationComposite();
	t2->addChild(new TransformScale(glm::vec3(scale)));
	t2->addChild(new TransformTranslate(glm::vec3(translation, 0.0f, 0.0f)));
	auto* o2 = new DrawableObject(sphereModel, shaderLambert, t2);
	o2->setColor(glm::vec3(0.385, 0.647, 0.812));
	scene->addObject(o2);

	// y gula
	auto* t3 = new TransformationComposite();
	t3->addChild(new TransformScale(glm::vec3(scale)));
	t3->addChild(new TransformTranslate(glm::vec3(0.0f, translation, 0.0f)));
	auto* o3 = new DrawableObject(sphereModel, shaderPhong, t3);
	o3->setColor(glm::vec3(0.385, 0.647, 0.812));
	scene->addObject(o3);

	// -y gula
	auto* t4 = new TransformationComposite();
	t4->addChild(new TransformScale(glm::vec3(scale)));
	t4->addChild(new TransformTranslate(glm::vec3(0.0f, -translation, 0.0f)));

	auto* o4 = new DrawableObject(sphereModel, shaderBlinn, t4);
	o4->setColor(glm::vec3(0.385, 0.647, 0.812));
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
	
	Model* plainModel = new Model(std::vector<float>(plain, plain + sizeof(plain) / sizeof(float)), 6, 3, 3);
	plainModel->setupMesh();

	size_t sphereSize = sizeof(sphere) / sizeof(float);
	Model* sphereModel = new Model(std::vector<float>(sphere, sphere + sphereSize), 6, 3, 3);
	sphereModel->setupMesh();

	size_t suziSize = sizeof(suziSmooth) / sizeof(float);
	Model* suziModel = new Model(std::vector<float>(suziSmooth, suziSmooth + suziSize), 6, 3, 3);
	suziModel->setupMesh();
	// float randomFloat = MIN + static_cast<float>(rand()) / RAND_MAX * (MAX - MIN);

	// svetlo

	auto* lightManager = new LightManager();

	// auto* sunLight = new Light(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f), 1.0f, 0.009f, 0.0032f);
	// lightManager->addLight(sunLight);

	scene->setLightManager(lightManager);

	auto* shaderLambert = shaderManager->clone("lambert");
	shaderLambert->setLightManager(lightManager);

	// shader sa pripojí na svetlá ako observer

	// môžeme použiť aj shader pre "constant" objekty (napr. slnko)
	auto* shaderConstant = shaderManager->get("constant");

	// zem
	auto* planeTransform = new TransformScale(glm::vec3(50.0f));
	auto* planeObj = new DrawableObject(plainModel, shaderLambert, planeTransform);
	planeObj->setColor(glm::vec3(0.41f, 0.65f, 0.17f)); // zelená tráva
	scene->addObject(planeObj);

	// slnko
	auto* sunTransform = new TransformationComposite(); 
	sunTransform->addChild(new TransformTranslate(glm::vec3(0.0f, 10.0f, 0.0f)));
	auto* sunObj = new DrawableObject(sphereModel, shaderManager->get("constant"), sunTransform);
	sunObj->setColor(glm::vec3(1.0f, 1.0f, 0.7f)); 
	scene->addObject(sunObj);

	int fireflyCount = 10;
	for (int i = 0; i < fireflyCount; i++) {
		// náhodná pozícia v priestore lesa
		float x = -250.0f + static_cast<float>(rand()) / RAND_MAX * 500.0f;
		float y = 24.0f + static_cast<float>(rand()) / RAND_MAX * 24.0f;
		float z = -150.0f + static_cast<float>(rand()) / RAND_MAX * 300.0f;

		// náhodný smer pohybu a rýchlosť
		glm::vec3 velocity = glm::vec3(
			-15.0f + static_cast<float>(rand()) / RAND_MAX * 30.0f,  
			-0.8f + static_cast<float>(rand()) / RAND_MAX * 1.6f,  
			-13.0f + static_cast<float>(rand()) / RAND_MAX * 26.0f
		);


		auto* fireflyLight = new Light(glm::vec3(x, y, z), glm::vec3(1.0f), 1.0f, 0.24f, 0.13f);
		lightManager->addLight(fireflyLight);

		// pohybová transformácia
		auto* transform = new TransformationComposite();
		transform->addChild(new TransformScale(glm::vec3(0.03f)));
		transform->addChild(new TransformRandomTranslate(glm::vec3(x, y, z)));
		

		// malá gulička (viditeľná)
		auto* firefly = new DrawableObject(sphereModel, shaderConstant, transform);
		firefly->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
		firefly->linkLight(fireflyLight);
		scene->addObject(firefly);
	}


	// stromy
	for (int i = 0; i < 75; i++)
	{	
		auto* transform = new TransformationComposite();

		float s = 0.2f + static_cast<float>(rand()) / RAND_MAX * 0.2f; // random scale
		float x = -50.0f + static_cast<float>(rand()) / RAND_MAX * 100.0f; 
		float z = -25.0f + static_cast<float>(rand()) / RAND_MAX * 50.0f; 

		transform->addChild(new TransformScale(glm::vec3(s)));
		transform->addChild(new TransformTranslate(glm::vec3(x, 0.0f, z)));

		auto* obj = new DrawableObject(treeModel, shaderLambert, transform);
		obj->setColor(glm::vec3(
			0.1f + 0.3f * (rand() / float(RAND_MAX)),
			0.4f + 0.4f * (rand() / float(RAND_MAX)),
			0.1f + 0.2f * (rand() / float(RAND_MAX))  
		));
		scene->addObject(obj);
	}
	// bushe
	for (int i = 0; i < 75; i++)
	{
		auto* transform = new TransformationComposite();

		float s = 1.5f + static_cast<float>(rand()) / RAND_MAX * 1.5f; 
		float x = -10.0f + static_cast<float>(rand()) / RAND_MAX * 20.0f; 
		float z = -5.0f + static_cast<float>(rand()) / RAND_MAX * 10.0f; 
		transform->addChild(new TransformScale(glm::vec3(s)));
		transform->addChild(new TransformTranslate(glm::vec3(x, 0.0f, z)));

		auto* obj = new DrawableObject(bushModel, shaderLambert, transform);
		obj->setColor(glm::vec3(0.07f, 0.23f, 0.06f));
		scene->addObject(obj);
	}
	
	// opice
	for (int i = 0; i < 5; i++)
	{
		auto* transform = new TransformationComposite();

		float s = 0.8f + static_cast<float>(rand()) / RAND_MAX * 0.8f;
		float x = -20.0f + static_cast<float>(rand()) / RAND_MAX * 40.0f;
		float z = -5.0f + static_cast<float>(rand()) / RAND_MAX * 10.0f;
		transform->addChild(new TransformScale(glm::vec3(s)));
		transform->addChild(new TransformTranslate(glm::vec3(x, 0.75f, z)));
		transform->addChild(new TransformDynamicRotate((5.0f + static_cast<float>(rand()) / RAND_MAX * 15.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

		auto* obj = new DrawableObject(suziModel, shaderLambert, transform);
		obj->setColor(glm::vec3(0.24f, 0.62f, 0.55f));
		scene->addObject(obj);
	}

	return scene;
}


Scene* SceneFactory::createScene4(ShaderManager* shaderManager) {
	auto* scene = new Scene();

	auto* lightManager = new LightManager();
	auto* light = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
	lightManager->addLight(light);
	size_t sphereSize = sizeof(sphere) / sizeof(float);
	auto* sphereModel = new Model(std::vector<float>(sphere, sphere + sphereSize), 6, 3, 3);
	sphereModel->setupMesh();

	auto* shaderConst = shaderManager->clone("constant");
	auto* shaderLambert = shaderManager->clone("lambert");

	shaderLambert->setLightManager(lightManager);


	// slnko
	auto* sunTransform = new TransformScale(glm::vec3(0.9f));
	auto* sun = new DrawableObject(sphereModel, shaderConst, sunTransform);
	sun->setColor(glm::vec3(1.0f, 1.0f, 0.7f));
	scene->addObject(sun);

	// zem
	auto* earthOrbit = new TransformationComposite();
	earthOrbit->addChild(new TransformDynamicRotate(5.0f, glm::vec3(0, 1, 0)));  // orbit okolo Slnka
	earthOrbit->addChild(new TransformTranslate(glm::vec3(4.0f, 0, 0)));         // vzdialenosť od Slnka
	earthOrbit->addChild(new TransformDynamicRotate(30.0f, glm::vec3(0, 1, 0))); // rotácia okolo osi
	earthOrbit->addChild(new TransformScale(glm::vec3(0.5f)));

	auto* earth = new DrawableObject(sphereModel, shaderLambert, earthOrbit);
	earth->setColor(glm::vec3(0.12f, 0.66f, 0.63f));
	scene->addObject(earth);

	// mesiac
	auto* moonOrbit = new TransformationComposite();
	moonOrbit->addChild(new TransformDynamicRotate(40.0f, glm::vec3(0, 1, 0)));  // orbit okolo Zeme
	moonOrbit->addChild(new TransformTranslate(glm::vec3(2.5f, 0, 0)));          // vzdialenosť od Zeme
	moonOrbit->addChild(new TransformScale(glm::vec3(0.2f)));

	auto* moonWorld = new TransformationComposite();
	moonWorld->addChild(earthOrbit);   
	moonWorld->addChild(moonOrbit);    // a potom svoj vlastný orbit

	auto* moon = new DrawableObject(sphereModel, shaderLambert, moonWorld);
	moon->setColor(glm::vec3(0.48f, 0.46f, 0.41f));
	scene->addObject(moon);

	return scene;
}
