#include "SceneFactory.h"
#include "DrawableObject.h"
#include "Model.h"
#include "TransformationComposite.h"
#include "TransformTranslate.h"
#include "TransformScale.h"
#include "TransformDynamicRotate.h"
#include "TransformRandomTranslate.h"
#include "TransformRotate.h"
#include "TransformLinearParametric.h"
#include "TransformBezier.h"
#include "TransformBezierSpline.h"
#include "TransformBezierSplineLoop.h"

#include <array>


#include <cstdlib>   // rand()
#include <ctime>     // time()

#include <glm/glm.hpp>

Scene* SceneFactory::createScene1(ShaderManager* shaderManager, ModelManager* modelManager) {
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


Scene* SceneFactory::createScene2(ShaderManager* shaderManager, ModelManager* modelManager) {
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

	Model* sphereModel = modelManager->get("sphere");

	float scale = 0.2f;
	float translation = 2.5f;

	// -x sphere
	auto* t1 = new TransformationComposite();
	t1->addChild(new TransformScale(glm::vec3(scale)));
	t1->addChild(new TransformTranslate(glm::vec3(-translation, 0.0f, 0.0f)));
	auto* o1 = new DrawableObject(sphereModel, shaderPhong, t1);
	o1->setColor(glm::vec3(0.385, 0.647, 0.812));
	scene->addObject(o1);

	// x sphere
	auto* t2 = new TransformationComposite();
	t2->addChild(new TransformScale(glm::vec3(scale)));
	t2->addChild(new TransformTranslate(glm::vec3(translation, 0.0f, 0.0f)));
	auto* o2 = new DrawableObject(sphereModel, shaderPhong, t2);
	o2->setColor(glm::vec3(0.385, 0.647, 0.812));
	scene->addObject(o2);

	// y sphere
	auto* t3 = new TransformationComposite();
	t3->addChild(new TransformScale(glm::vec3(scale)));
	t3->addChild(new TransformTranslate(glm::vec3(0.0f, translation, 0.0f)));
	auto* o3 = new DrawableObject(sphereModel, shaderPhong, t3);
	o3->setColor(glm::vec3(0.385, 0.647, 0.812));
	scene->addObject(o3);

	// -y sphere
	auto* t4 = new TransformationComposite();
	t4->addChild(new TransformScale(glm::vec3(scale)));
	t4->addChild(new TransformTranslate(glm::vec3(0.0f, -translation, 0.0f)));

	auto* o4 = new DrawableObject(sphereModel, shaderPhong, t4);
	o4->setColor(glm::vec3(0.385, 0.647, 0.812));
	scene->addObject(o4);

	return scene;
}

DrawableObject* SceneFactory::createTree(Model* model, ShaderProgram* shaderProgram, const glm::vec3& position) {
	auto* transform = new TransformationComposite();

	float s = 0.2f + static_cast<float>(rand()) / RAND_MAX * 0.2f;

	transform->addChild(new TransformTranslate(position));
	transform->addChild(new TransformScale(glm::vec3(s)));

	auto* obj = new DrawableObject(model, shaderProgram, transform);

	obj->setColor(glm::vec3(
		0.1f + 0.3f * (rand() / float(RAND_MAX)),
		0.4f + 0.4f * (rand() / float(RAND_MAX)),
		0.1f + 0.2f * (rand() / float(RAND_MAX))
	));

	return obj;
}


Scene* SceneFactory::createScene3(ShaderManager* shaderManager, ModelManager* modelManager) {

	srand((unsigned)time(nullptr));
	auto* scene = new Scene();

	Model* treeModel = modelManager->get("tree");

	Model* bushModel = modelManager->get("bush");
	
	Model* plainModel = modelManager->get("plain");

	Model* sphereModel = modelManager->get("sphere");

	Model* suziModel = modelManager->get("suzi");

	// float randomFloat = MIN + static_cast<float>(rand()) / RAND_MAX * (MAX - MIN);

	// light

	auto* lightManager = new LightManager();
	auto* sunLight = new Light(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f), 1.0f, 0.002f, 0.0009f);
	lightManager->addLight(sunLight);

	scene->setLightManager(lightManager);

	auto* shaderLambert = shaderManager->clone("lambert");
	auto* shaderPhong = shaderManager->clone("phong");
	auto* shaderBlinn = shaderManager->clone("blinn");

	shaderLambert->setLightManager(lightManager);
	shaderPhong->setLightManager(lightManager);
	shaderBlinn->setLightManager(lightManager);


	auto* shaderConstant = shaderManager->get("constant");

	// skybox
	auto* shaderSky = shaderManager->clone("skybox");
	std::array<std::string, 6> faces = {
		"Assets/aurora/px.png",
		"Assets/aurora/nx.png",
		"Assets/aurora/py.png",
		"Assets/aurora/ny.png",
		"Assets/aurora/pz.png",
		"Assets/aurora/nz.png"
	};

	auto* skybox = new Skybox(shaderSky, faces);
	scene->setSkybox(skybox);

	// grass
	auto* planeTransform = new TransformScale(glm::vec3(50.0f));
	auto* planeObj = new DrawableObject(plainModel, shaderLambert, planeTransform);
	
	Texture* grassTexture = new Texture("Assets/grass.png");
	
	planeObj->setColor(glm::vec3(0.41f, 0.65f, 0.17f)); 
	planeObj->setTexture(grassTexture);
	scene->addObject(planeObj);

	// sun
	auto* sunTransform = new TransformationComposite(); 
	sunTransform->addChild(new TransformTranslate(glm::vec3(0.0f, 10.0f, 0.0f)));
	auto* sunObj = new DrawableObject(sphereModel, shaderManager->get("constant"), sunTransform);
	sunObj->setColor(glm::vec3(1.0f, 1.0f, 0.7f)); 
	scene->addObject(sunObj);

	int fireflyCount = 10;
	for (int i = 0; i < fireflyCount; i++) {
		// random position
		float x = -400.0f + static_cast<float>(rand()) / RAND_MAX * 800.0f;
		float y = 24.0f + static_cast<float>(rand()) / RAND_MAX * 24.0f;
		float z = -350.0f + static_cast<float>(rand()) / RAND_MAX * 700.0f;

		auto* fireflyLight = new Light(glm::vec3(x, y, z), glm::vec3(1.0f, 0.9f, 0.6f));
		fireflyLight->setAttenuation(1.0f, 0.9f, 1.5f); 
		lightManager->addLight(fireflyLight);

		// translate
		auto* transform = new TransformationComposite();
		transform->addChild(new TransformScale(glm::vec3(0.015f)));
		transform->addChild(new TransformRandomTranslate(glm::vec3(x, y, z)));
		

		auto* firefly = new DrawableObject(sphereModel, shaderConstant, transform);
		firefly->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
		firefly->linkLight(fireflyLight);
		scene->addObject(firefly);
	}


	// trees
	for (int i = 0; i < 75; i++)
	{	
		auto* transform = new TransformationComposite();

		float s = 0.2f + static_cast<float>(rand()) / RAND_MAX * 0.2f; // random scale
		float x = -15.0f + static_cast<float>(rand()) / RAND_MAX * 30.0f; 
		float z = -15.0f + static_cast<float>(rand()) / RAND_MAX * 30.0f; 
		glm::vec3 pos(x, 0, z);


		scene->addObject(
			SceneFactory::createTree(treeModel, shaderLambert, pos)
		);
	}
	// bushes
	for (int i = 0; i < 75; i++)
	{
		auto* transform = new TransformationComposite();

		float s = 1.5f + static_cast<float>(rand()) / RAND_MAX * 1.5f; 
		float x = -10.0f + static_cast<float>(rand()) / RAND_MAX * 20.0f; 
		float z = -5.0f + static_cast<float>(rand()) / RAND_MAX * 10.0f; 
		transform->addChild(new TransformScale(glm::vec3(s)));
		transform->addChild(new TransformTranslate(glm::vec3(x, 0.0f, z)));

		auto* obj = new DrawableObject(bushModel, shaderBlinn, transform);
		obj->setColor(glm::vec3(0.07f, 0.23f, 0.06f));
		scene->addObject(obj);
	}
	


	Model* fionaModel = modelManager->get("fiona");
	auto* fionaTex = new Texture("Assets/fiona.png");
	auto* fionaTr = new TransformationComposite();
	fionaTr->addChild(new TransformScale(glm::vec3(0.9f)));
	fionaTr->addChild(new TransformTranslate(glm::vec3(-10.0f, 0.0f, -10.0f)));

	auto* fiona = new DrawableObject(fionaModel, shaderPhong, fionaTr);
	fiona->setTexture(fionaTex);
	scene->addObject(fiona);


	Model* shrekModel = modelManager->get("shrek");
	auto* shrekTex = new Texture("Assets/shrek.png");
	auto* shrekTr = new TransformationComposite();
	shrekTr->addChild(new TransformScale(glm::vec3(0.9f)));
	shrekTr->addChild(new TransformTranslate(glm::vec3(-6.0f, 0.0f, -10.0f)));

	auto* shrek = new DrawableObject(shrekModel, shaderPhong, shrekTr);
	shrek->setTexture(shrekTex);
	scene->addObject(shrek);

	Model* toiletModel = modelManager->get("toiled");
	auto* toiletTex = new Texture("Assets/toiled.jpg");
	auto* toiletTr = new TransformationComposite();
	toiletTr->addChild(new TransformScale(glm::vec3(0.9f)));
	toiletTr->addChild(new TransformTranslate(glm::vec3(-8.0f, 0.0f, -10.0f)));

	auto* toilet = new DrawableObject(toiletModel, shaderLambert, toiletTr);
	toilet->setTexture(toiletTex);
	scene->addObject(toilet);


	return scene;
}


Scene* SceneFactory::createScene4(ShaderManager* shaderManager, ModelManager* modelManager) {
	auto* scene = new Scene();

	auto* lightManager = new LightManager();
	auto* light = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.0f, 0.0f);
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


	Model* loginModel = modelManager->get("login");


	// sun
	Model* sphereModel = modelManager->get("sphereWithUV");

	Texture* sunTex = new Texture("Assets/sun.jpg");
	auto* sunTransform = new TransformationComposite();
	sunTransform->addChild(new TransformScale(glm::vec3(3.0f)));
	sunTransform->addChild(new TransformDynamicRotate(1.0f, glm::vec3(0, 1, 0)));
	auto* sun = new DrawableObject(sphereModel, shaderConst, sunTransform);
	sun->setTexture(sunTex);
	// sun->setColor(glm::vec3(1.0f, 1.0f, 0.7f));
	scene->addObject(sun);


	// mercury
	auto* mercurOrbit = new TransformationComposite();
	mercurOrbit->addChild(new TransformDynamicRotate(6.0f, glm::vec3(0, 1, 0))); // sun orbit
	mercurOrbit->addChild(new TransformTranslate(glm::vec3(6.0f, 0, 0))); 
	mercurOrbit->addChild(new TransformDynamicRotate(2.0f, glm::vec3(0, 1, 0))); // self orbit
	mercurOrbit->addChild(new TransformScale(glm::vec3(0.2f)));
	Texture* mercuryTex = new Texture("Assets/mercury.jpg");
	auto* mercury = new DrawableObject(sphereModel, shaderLambert, mercurOrbit);
	mercury->setTexture(mercuryTex);
	scene->addObject(mercury);

	// venus
	auto* venusOrbit = new TransformationComposite();
	venusOrbit->addChild(new TransformDynamicRotate(3.0f, glm::vec3(0, 1, 0))); // sun orbit
	venusOrbit->addChild(new TransformTranslate(glm::vec3(9.0f, 0, 0)));
	venusOrbit->addChild(new TransformDynamicRotate(-5.0f, glm::vec3(0, 1, 0)));  // self orbit
	venusOrbit->addChild(new TransformScale(glm::vec3(0.45f)));
	Texture* venusTex = new Texture("Assets/venus.jpg");
	auto* venus = new DrawableObject(sphereModel, shaderLambert, venusOrbit);
	venus->setTexture(venusTex);
	scene->addObject(venus);


	// earth
	auto* earthOrbit = new TransformationComposite();
	earthOrbit->addChild(new TransformDynamicRotate(2.0f, glm::vec3(0, 1, 0)));  // sun orbit
	earthOrbit->addChild(new TransformTranslate(glm::vec3(12.0f, 0, 0)));         
	earthOrbit->addChild(new TransformRotate(glm::radians(23.5f), glm::vec3(0, 0, 1)));	
	earthOrbit->addChild(new TransformDynamicRotate(30.0f, glm::vec3(0, 1, 0))); // self orbit
	earthOrbit->addChild(new TransformScale(glm::vec3(0.5f)));

	Texture* earthTex = new Texture("Assets/earth.jpg");
	auto* earth = new DrawableObject(sphereModel, shaderLambert, earthOrbit);
	earth->setTexture(earthTex);
	// earth->setColor(glm::vec3(0.12f, 0.66f, 0.63f));
	scene->addObject(earth);

	// moon
	auto* moonOrbit = new TransformationComposite();
	moonOrbit->addChild(new TransformDynamicRotate(10.0f, glm::vec3(0, 1, 0)));  // earth orbit
	moonOrbit->addChild(new TransformTranslate(glm::vec3(0.7f, 0, 0)));          
	moonOrbit->addChild(new TransformRotate(glm::radians(5.14f), glm::vec3(0, 0, 1))); 
	moonOrbit->addChild(new TransformScale(glm::vec3(0.13f)));

	auto* moonWorld = new TransformationComposite();
	moonWorld->addChild(new TransformDynamicRotate(2.0f, glm::vec3(0, 1, 0)));  // same as earth
	moonWorld->addChild(new TransformTranslate(glm::vec3(12.0f, 0.0f, 0.0f))); 
	moonWorld->addChild(moonOrbit);    // own orbit

	auto* loginT = new TransformationComposite();
	loginT->addChild(new TransformDynamicRotate(2.0f, glm::vec3(0, 1, 0)));
	loginT->addChild(new TransformTranslate(glm::vec3(12.0f, 0.0f, 0.0f)));
	loginT->addChild(new TransformDynamicRotate(-10.0f, glm::vec3(0, 1, 0))); 
	loginT->addChild(new TransformTranslate(glm::vec3(0.7f, 0, 0)));          


	auto* loginObj = new DrawableObject(loginModel, shaderLambert, loginT);
	scene->addObject(loginObj);

	Texture* moonTex = new Texture("Assets/moon.jpg");
	auto* moon = new DrawableObject(sphereModel, shaderLambert, moonWorld);
	moon->setTexture(moonTex);
	// moon->setColor(glm::vec3(0.48f, 0.46f, 0.41f));
	scene->addObject(moon);

	// mars
	auto* marsOrbit = new TransformationComposite();
	marsOrbit->addChild(new TransformDynamicRotate(1.0f, glm::vec3(0, 1, 0))); // sun orbit
	marsOrbit->addChild(new TransformTranslate(glm::vec3(18.0f, 0, 0)));
	marsOrbit->addChild(new TransformDynamicRotate(24.0f, glm::vec3(0, 1, 0)));  // self orbit
	marsOrbit->addChild(new TransformScale(glm::vec3(0.27f)));

	Texture* marsTex = new Texture("Assets/mars.jpg");
	auto* mars = new DrawableObject(sphereModel, shaderLambert, marsOrbit);
	mars->setTexture(marsTex);
	scene->addObject(mars);

	// jupyter
	auto* jupiterOrbit = new TransformationComposite();
	jupiterOrbit->addChild(new TransformDynamicRotate(0.5f, glm::vec3(0, 1, 0))); // sun orbit
	jupiterOrbit->addChild(new TransformTranslate(glm::vec3(30.0f, 0, 0))); 
	jupiterOrbit->addChild(new TransformDynamicRotate(50.0f, glm::vec3(0, 1, 0)));  // self orbit
	jupiterOrbit->addChild(new TransformScale(glm::vec3(1.4f)));

	Texture* jupiterTex = new Texture("Assets/jupiter.jpg");
	auto* jupiter = new DrawableObject(sphereModel, shaderLambert, jupiterOrbit);
	jupiter->setTexture(jupiterTex);
	scene->addObject(jupiter);


	// saturn
	auto* saturnOrbit = new TransformationComposite();
	saturnOrbit->addChild(new TransformDynamicRotate(0.35f, glm::vec3(0, 1, 0)));   // sun orbit
	saturnOrbit->addChild(new TransformTranslate(glm::vec3(42.0f, 0, 0)));          
	saturnOrbit->addChild(new TransformRotate(glm::radians(26.7f), glm::vec3(0, 0, 1))); 
	saturnOrbit->addChild(new TransformDynamicRotate(40.0f, glm::vec3(0, 1, 0)));   // self orbit
	saturnOrbit->addChild(new TransformScale(glm::vec3(1.2f)));                   

	Texture* saturnTex = new Texture("Assets/saturn.jpg");
	auto* saturn = new DrawableObject(sphereModel, shaderLambert, saturnOrbit);
	saturn->setTexture(saturnTex);
	scene->addObject(saturn);


	// uranus
	auto* uranusOrbit = new TransformationComposite();
	uranusOrbit->addChild(new TransformDynamicRotate(0.25f, glm::vec3(0, 1, 0)));    // sun orbit
	uranusOrbit->addChild(new TransformTranslate(glm::vec3(54.0f, 0, 0)));           
	uranusOrbit->addChild(new TransformRotate(glm::radians(98.0f), glm::vec3(1, 0, 0))); 
	uranusOrbit->addChild(new TransformDynamicRotate(30.0f, glm::vec3(0, 1, 0)));    // self orbit
	uranusOrbit->addChild(new TransformScale(glm::vec3(0.6f)));                     

	Texture* uranusTex = new Texture("Assets/uranus.jpg");
	auto* uranus = new DrawableObject(sphereModel, shaderLambert, uranusOrbit);
	uranus->setTexture(uranusTex);
	scene->addObject(uranus);
	
	
	// neptune
	auto* neptuneOrbit = new TransformationComposite();
	neptuneOrbit->addChild(new TransformDynamicRotate(0.2f, glm::vec3(0, 1, 0)));   // sun orbit
	neptuneOrbit->addChild(new TransformTranslate(glm::vec3(66.0f, 0, 0)));         
	neptuneOrbit->addChild(new TransformDynamicRotate(28.0f, glm::vec3(0, 1, 0)));  // self orbit
	neptuneOrbit->addChild(new TransformScale(glm::vec3(0.58f)));                   

	Texture* neptuneTex = new Texture("Assets/neptune.jpg");
	auto* neptune = new DrawableObject(sphereModel, shaderLambert, neptuneOrbit);
	neptune->setTexture(neptuneTex);
	scene->addObject(neptune);

	return scene;
}

Scene* SceneFactory::createScene5(ShaderManager* shaderManager, ModelManager* modelManager) {
	auto* scene = new Scene();

	auto* shaderLambert = shaderManager->clone("lambert");
	auto* shaderPhong = shaderManager->clone("phong");


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


	auto* lightManager = new LightManager();
	scene->setLightManager(lightManager);

	auto* light = new Light(glm::vec3(0.0f, 25.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	auto* lightAboveFiona = new Light(glm::vec3(-13.0f, 15.0f, -10.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	Model* plainModel = modelManager->get("plain");
	auto* planeTransform = new TransformScale(glm::vec3(50.0f));
	auto* planeObj = new DrawableObject(plainModel, shaderLambert, planeTransform);

	Texture* grassTexture = new Texture("Assets/grass.png");

	planeObj->setTexture(grassTexture);
	scene->addObject(planeObj);

	lightManager->addLight(light);
	// lightManager->addLight(lightAboveFiona);

	scene->setLightManager(lightManager);
	shaderLambert->setLightManager(lightManager);
	shaderPhong->setLightManager(lightManager);

	
	Model* formulaModel = modelManager->get("formula");
	auto* formulaTransform = new TransformationComposite();

	std::vector<glm::vec3> track;

	float radius = 30.0f;
	for (int i = 0; i < 12; i++) {
		float angle = glm::radians(i * 30.0f);
		float x = radius * cos(angle);
		float z = radius * sin(angle);
		track.push_back(glm::vec3(x, 0.0f, z));
	}
	track.push_back(track[0]);


	while ((track.size() - 1) % 3 != 0) {
		track.insert(track.end() - 1, track[track.size() - 2]);
	}

	auto* spline = new TransformBezierSplineLoop(track, 0.1f);
	formulaTransform->addChildAtBeginning(spline);


	formulaTransform->addChild(
		new TransformRotate(glm::radians(+90.0f), glm::vec3(0, 1, 0))
	);
	formulaTransform->addChild(new TransformScale(glm::vec3(0.2f, 0.2f, 0.2f)));
	auto* formula = new DrawableObject(formulaModel, shaderLambert, formulaTransform);
	formula->setColor(glm::vec3(0.8f, 0.8f, 0.7f));

	Material formulaMat;
	formulaMat.ra = 0.1f;   
	formulaMat.rd = 0.7f;   
	formulaMat.rs = 0.8f;   
	formulaMat.h = 64.0f;  

	formula->setMaterial(formulaMat);
	scene->addObject(formula);

	Model* hamburgerModel = modelManager->get("hamburger");
	auto* hamburgerTransform = new TransformationComposite();
	hamburgerTransform->addChild(new TransformScale(glm::vec3(0.5f, 0.5f, 0.5f)));
	hamburgerTransform->addChild(new TransformTranslate(glm::vec3(30.f, 0.0f, 30.0f)));

	auto* hamburger = new DrawableObject(hamburgerModel, shaderLambert, hamburgerTransform);
	hamburger->setColor(glm::vec3(0.8f, 0.8f, 0.7f));
	// scene->addObject(hamburger);

	return scene;
}

Scene* SceneFactory::createScene6(ShaderManager* shaderManager, ModelManager* modelManager) {
	auto* scene = new Scene();
	auto* lightManager = new LightManager();
	scene->setLightManager(lightManager);

	auto* light = new Light(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f));
	lightManager->addLight(light);

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


	Model* plainModel = modelManager->get("plain");
	auto* shaderLambert = shaderManager->clone("lambert");
	shaderLambert->setLightManager(lightManager);
	auto* planeTransform = new TransformScale(glm::vec3(50.0f));
	auto* planeObj = new DrawableObject(plainModel, shaderLambert, planeTransform);

	Texture* grassTexture = new Texture("Assets/grass.png");

	planeObj->setColor(glm::vec3(0.41f, 0.65f, 0.17f)); 
	planeObj->setTexture(grassTexture);
	scene->addObject(planeObj);


	return scene;

}
