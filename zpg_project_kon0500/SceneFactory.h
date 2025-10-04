#pragma once
#include "Scene.h"
#include "ShaderProgram.h"
#include <string>
#include <map>

#include "TransformationComposite.h"
#include "TransformTranslate.h"
#include "TransformScale.h"
#include "TransformDynamicRotate.h"


class SceneFactory
{
public:
	static Scene* createScene1(std::map<std::string, ShaderProgram*>& shaders);
	static Scene* createScene2(std::map<std::string, ShaderProgram*>& shaders);
	static Scene* createScene3(std::map<std::string, ShaderProgram*>& shaders);
};

