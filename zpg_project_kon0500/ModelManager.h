#pragma once
#include <string>
#include <map>
#include <vector>
#include "Model.h"

#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/gift.h"
#include "Models/plain.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Models/sphere.h"

class ModelManager
{
private:
	std::map<std::string, Model*> models;

public:
	~ModelManager();

	void loadFromObj(const std::string&name, const::std::string& filename);

	void loadFromData(const std::string& name, 
		const std::vector<float>& vertices, 
		int stride, int positionSize, int normalSize, int uvSize = 0);

	Model* get(const std::string& name);

	void createModels();
};

