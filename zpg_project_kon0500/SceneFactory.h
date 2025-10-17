#pragma once
#include "Scene.h"
#include "ShaderProgram.h"
#include <string>
#include <map>
#include "ShaderManager.h"
#include "Light.h"

#include "TransformationComposite.h"
#include "TransformTranslate.h"
#include "TransformScale.h"
#include "TransformDynamicRotate.h"


class SceneFactory
{
public:
	static Scene* createScene1(ShaderManager* shaderManager);
	static Scene* createScene2(ShaderManager* shaderManager);
	static Scene* createScene3(ShaderManager* shaderManager);
	static Scene* createScene4(ShaderManager* shaderManager);

};

