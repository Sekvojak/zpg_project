#include "ShootingRange.h"
#include <cstdlib>


ShootingRange::ShootingRange(Scene* scene, Model* tarModel, ShaderProgram* tarShader) {
	this->scene = scene;
	this->targetModel = tarModel;
	this->targetShader = tarShader;
	this->shrekTexture = new Texture("Assets/shrek.png");
}

void ShootingRange::spawnTarget() {
	float zLevels[3] = { -10.0f, -15.0f, -20.0f };
	float z = zLevels[rand() % 3];

	bool leftToRight = rand() % 2;

	glm::vec3 A, B;


	if (leftToRight) {
		A = glm::vec3(-20, 1, z);
		B = glm::vec3(20, 1, z);
	}
	else {
		A = glm::vec3(20, 1, z);
		B = glm::vec3(-20, 1, z);
	}
	// float randomFloat = MIN + static_cast<float>(rand()) / RAND_MAX * (MAX - MIN);
	float scale = 0.9f + static_cast<float>(rand()) / RAND_MAX * (1.4 - 0.9);  
	float speed = 0.3f + static_cast<float>(rand()) / RAND_MAX * (0.45 - 0.3);

	auto* move = new TransformLinearParametric(A, B, speed);
	auto* composite = new TransformationComposite();
	composite->addChild(new TransformScale(glm::vec3(scale)));
	composite->addChild(move);

	auto* obj = new DrawableObject(targetModel, targetShader, composite);
	obj->setColor(glm::vec3(1, 0, 0));

	obj->setTexture(shrekTexture);

	scene->addObject(obj); 
	targets.push_back({ obj, move });
}

void ShootingRange::update(float dt) {
	for (int i = 0; i < targets.size(); i++)
	{
		Target& t = targets[i];
		if (t.movement->finished())
		{
			scene->removeObject(t.object);
			targets.erase(targets.begin() + i);
			--i;

			spawnTarget();
		}
	}
}

void ShootingRange::onClick(int id) {
	for (int i = 0; i < targets.size(); i++)
	{
		if (targets[i].object->getID() == id)
		{
			scene->removeObject(targets[i].object);

			targets.erase(targets.begin() + i);

			score++;
			std::cout << score << std::endl;
			spawnTarget();
			return;
		}
	}
}