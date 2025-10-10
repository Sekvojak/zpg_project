#pragma once
#include <map>
#include <string>
#include "ShaderProgram.h"
#include "Camera.h"

class ShaderManager
{
private:
	std::map<std::string, ShaderProgram*> shaders;

public:
	void createShaders(Camera* camera);
	ShaderProgram* get(const std::string& name);
	void cleanup();
	~ShaderManager();

};

