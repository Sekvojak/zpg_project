#pragma once
#include "Scene.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "TransformLinearParametric.h"
#include "TransformationComposite.h"
#include "TransformScale.h"
#include "Texture.h"

struct Target {
	DrawableObject* object;
	TransformLinearParametric* movement;
};


class ShootingRange
{
private:
	Scene* scene;
	Model* targetModel;
	ShaderProgram* targetShader;
	Texture* shrekTexture = nullptr;


	std::vector<Target> targets;
	int score = 0;

public:
	ShootingRange(Scene* scene, Model* tarModel, ShaderProgram* tarShader);
	void update(float  dt);
	void onClick(int selectedID);
	void spawnTarget();
	int getScore() const { return score; }

};

