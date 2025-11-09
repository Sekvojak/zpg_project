#include "SceneFactory.h"
#include "DrawableObject.h"
#include "Model.h"
#include "TransformationComposite.h"
#include "TransformTranslate.h"
#include "TransformScale.h"
#include "TransformDynamicRotate.h"
#include "TransformRandomTranslate.h"
#include "TransformRotate.h"
#include <array>


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

	auto* lightManager = new LightManager();
	scene->setLightManager(lightManager);

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
	auto* o1 = new DrawableObject(sphereModel, shaderPhong, t1);
	o1->setColor(glm::vec3(0.385, 0.647, 0.812));
	scene->addObject(o1);

	// x gula
	auto* t2 = new TransformationComposite();
	t2->addChild(new TransformScale(glm::vec3(scale)));
	t2->addChild(new TransformTranslate(glm::vec3(translation, 0.0f, 0.0f)));
	auto* o2 = new DrawableObject(sphereModel, shaderPhong, t2);
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

	auto* o4 = new DrawableObject(sphereModel, shaderPhong, t4);
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
	
	Model* plainModel = new Model(std::vector<float>(plain, plain + sizeof(plain) / sizeof(float)), 8, 3, 3, 2);
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
	auto* sunLight = new Light(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f), 1.0f, 0.002f, 0.0009f);
	lightManager->addLight(sunLight);

	scene->setLightManager(lightManager);

	auto* shaderLambert = shaderManager->clone("lambert");
	auto* shaderPhong = shaderManager->clone("phong");
	shaderLambert->setLightManager(lightManager);
	shaderPhong->setLightManager(lightManager);

	auto* shaderConstant = shaderManager->get("constant");

	// skybox
	auto* shaderSky = shaderManager->clone("skybox");
	std::array<std::string, 6> faces = {
		"Assets/skybox2/px.png",
		"Assets/skybox2/nx.png",
		"Assets/skybox2/py.png",
		"Assets/skybox2/ny.png",
		"Assets/skybox2/pz.png",
		"Assets/skybox2/nz.png"
	};

	auto* skybox = new Skybox(shaderSky, faces);
	scene->setSkybox(skybox);

	// zem
	auto* planeTransform = new TransformScale(glm::vec3(50.0f));
	auto* planeObj = new DrawableObject(plainModel, shaderLambert, planeTransform);
	
	Texture* grassTexture = new Texture("grass.png");
	
	planeObj->setColor(glm::vec3(0.41f, 0.65f, 0.17f)); // zelená tráva
	planeObj->setTexture(grassTexture);
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
		float x = -300.0f + static_cast<float>(rand()) / RAND_MAX * 600.0f;
		float y = 24.0f + static_cast<float>(rand()) / RAND_MAX * 24.0f;
		float z = -250.0f + static_cast<float>(rand()) / RAND_MAX * 500.0f;

		auto* fireflyLight = new Light(glm::vec3(x, y, z), glm::vec3(1.0f, 0.9f, 0.6f));
		fireflyLight->setAttenuation(1.0f, 0.9f, 1.5f); // slabší dosah
		lightManager->addLight(fireflyLight);

		// pohybová transformácia
		auto* transform = new TransformationComposite();
		transform->addChild(new TransformScale(glm::vec3(0.015f)));
		transform->addChild(new TransformRandomTranslate(glm::vec3(x, y, z)));
		

		// malá gulička 
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
	


	Model* fionaModel = new Model("fiona.obj");
	auto* fionaTex = new Texture("Assets/fiona.png");
	auto* fionaTr = new TransformationComposite();
	fionaTr->addChild(new TransformScale(glm::vec3(0.9f)));
	fionaTr->addChild(new TransformTranslate(glm::vec3(-10.0f, 0.0f, -10.0f)));

	auto* fiona = new DrawableObject(fionaModel, shaderPhong, fionaTr);
	fiona->setTexture(fionaTex);
	scene->addObject(fiona);


	Model* shrekModel = new Model("shrek.obj");
	auto* shrekTex = new Texture("Assets/shrek.png");
	auto* shrekTr = new TransformationComposite();
	shrekTr->addChild(new TransformScale(glm::vec3(0.9f)));
	shrekTr->addChild(new TransformTranslate(glm::vec3(-6.0f, 0.0f, -10.0f)));

	auto* shrek = new DrawableObject(shrekModel, shaderPhong, shrekTr);
	shrek->setTexture(shrekTex);
	scene->addObject(shrek);

	Model* toiletModel = new Model("toiled.obj");
	auto* toiletTex = new Texture("Assets/toiled.jpg");
	auto* toiletTr = new TransformationComposite();
	toiletTr->addChild(new TransformScale(glm::vec3(0.9f)));
	toiletTr->addChild(new TransformTranslate(glm::vec3(-8.0f, 0.0f, -10.0f)));

	auto* toilet = new DrawableObject(toiletModel, shaderLambert, toiletTr);
	toilet->setTexture(toiletTex);
	scene->addObject(toilet);


	return scene;
}


Scene* SceneFactory::createScene4(ShaderManager* shaderManager) {
	auto* scene = new Scene();

	auto* lightManager = new LightManager();
	auto* light = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
	lightManager->addLight(light);

	scene->setLightManager(lightManager);

	auto* shaderConst = shaderManager->clone("constant");
	auto* shaderLambert = shaderManager->clone("lambert");

	shaderLambert->setLightManager(lightManager);

	// skybox
	auto* shaderSky = shaderManager->clone("skybox");
	std::array<std::string, 6> faces = {
		"Assets/skyboxGalaxy/px.jpg",
		"Assets/skyboxGalaxy/nx.jpg",
		"Assets/skyboxGalaxy/py.jpg",
		"Assets/skyboxGalaxy/ny.jpg",
		"Assets/skyboxGalaxy/pz.jpg",
		"Assets/skyboxGalaxy/nz.jpg"
	};

	auto* skybox = new Skybox(shaderSky, faces);
	scene->setSkybox(skybox);


	// slnko
	Model* sphereModel = new Model("sphere.obj");
	Texture* sunTex = new Texture("Assets/sun.jpg");
	auto* sunTransform = new TransformScale(glm::vec3(0.9f));
	auto* sun = new DrawableObject(sphereModel, shaderConst, sunTransform);
	sun->setTexture(sunTex);
	// sun->setColor(glm::vec3(1.0f, 1.0f, 0.7f));
	scene->addObject(sun);

	// zem
	auto* earthOrbit = new TransformationComposite();
	earthOrbit->addChild(new TransformDynamicRotate(5.0f, glm::vec3(0, 1, 0)));  // orbit okolo Slnka
	earthOrbit->addChild(new TransformTranslate(glm::vec3(4.0f, 0, 0)));         // vzdialenosť od Slnka
	earthOrbit->addChild(new TransformDynamicRotate(30.0f, glm::vec3(0, 1, 0))); // rotácia okolo osi
	earthOrbit->addChild(new TransformScale(glm::vec3(0.5f)));

	Texture* earthTex = new Texture("Assets/earth.jpg");
	auto* earth = new DrawableObject(sphereModel, shaderLambert, earthOrbit);
	earth->setTexture(earthTex);
	// earth->setColor(glm::vec3(0.12f, 0.66f, 0.63f));
	scene->addObject(earth);

	// mesiac
	auto* moonOrbit = new TransformationComposite();
	moonOrbit->addChild(new TransformDynamicRotate(40.0f, glm::vec3(0, 1, 0)));  // orbit okolo Zeme
	moonOrbit->addChild(new TransformTranslate(glm::vec3(2.5f, 0, 0)));          // vzdialenosť od Zeme
	moonOrbit->addChild(new TransformScale(glm::vec3(0.2f)));

	auto* moonWorld = new TransformationComposite();
	moonWorld->addChild(earthOrbit);   
	moonWorld->addChild(moonOrbit);    // a potom svoj vlastný orbit

	Texture* moonTex = new Texture("Assets/moon.jpg");
	auto* moon = new DrawableObject(sphereModel, shaderLambert, moonWorld);
	moon->setTexture(moonTex);
	// moon->setColor(glm::vec3(0.48f, 0.46f, 0.41f));
	scene->addObject(moon);

	return scene;
}

Scene* SceneFactory::createScene5(ShaderManager* shaderManager) {
	auto* scene = new Scene();

	auto* shaderLambert = shaderManager->clone("lambert");
	auto* shaderPhong = shaderManager->clone("phong");

	auto* lightManager = new LightManager();
	scene->setLightManager(lightManager);

	auto* light = new Light(glm::vec3(0.0f, 25.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	auto* lightAboveFiona = new Light(glm::vec3(-13.0f, 15.0f, -10.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	lightManager->addLight(light);
	lightManager->addLight(lightAboveFiona);

	scene->setLightManager(lightManager);
	shaderLambert->setLightManager(lightManager);
	shaderPhong->setLightManager(lightManager);

	
	Model* formulaModel = new Model("formula1.obj");
	auto* formulaTransform = new TransformationComposite();
	formulaTransform->addChild(new TransformScale(glm::vec3(0.2f, 0.2f, 0.2f)));
	auto* formula = new DrawableObject(formulaModel, shaderLambert, formulaTransform);
	formula->setColor(glm::vec3(0.8f, 0.8f, 0.7f));
	scene->addObject(formula);

	Model* hamburgerModel = new Model("Hamburger_01.obj");
	auto* hamburgerTransform = new TransformationComposite();
	hamburgerTransform->addChild(new TransformScale(glm::vec3(0.5f, 0.5f, 0.5f)));
	hamburgerTransform->addChild(new TransformTranslate(glm::vec3(30.f, 0.0f, 30.0f)));

	auto* hamburger = new DrawableObject(hamburgerModel, shaderLambert, hamburgerTransform);
	hamburger->setColor(glm::vec3(0.8f, 0.8f, 0.7f));
	scene->addObject(hamburger);

	return scene;
}