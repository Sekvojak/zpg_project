#pragma once
#include "Scene.h"
#include "ShaderProgram.h"
#include <string>
#include <map>
#include "ShaderManager.h"
#include "ModelManager.h"
#include "Light.h"

#include "TransformationComposite.h"
#include "TransformTranslate.h"
#include "TransformScale.h"
#include "TransformDynamicRotate.h"

#include "DrawableObject.h"

class SceneFactory
{
public:
	static Scene* createScene1(ShaderManager* shaderManager, ModelManager* modelManager);
	static Scene* createScene2(ShaderManager* shaderManager, ModelManager* modelManager);
	static DrawableObject* createTree(Model* treeModel, ShaderProgram* shaderProgram, const glm::vec3& position);
	static Scene* createScene3(ShaderManager* shaderManager, ModelManager* modelManager);
	static Scene* createScene4(ShaderManager* shaderManager, ModelManager* modelManager);
	static Scene* createScene5(ShaderManager* shaderManager, ModelManager* modelManager);

};

