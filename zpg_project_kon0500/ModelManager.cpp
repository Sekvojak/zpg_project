#include "ModelManager.h"

void ModelManager::loadFromObj(const std::string& name, const std::string& filename) {
    models[name] = new Model(filename.c_str());
}

void ModelManager::loadFromData(const std::string& name,
    const std::vector<float>& vertices,
    int stride, int positionSize, int normalSize, int uvSize) {
    models[name] = new Model(vertices, stride, positionSize, normalSize, uvSize);
    models[name]->setupMesh();   
}

Model* ModelManager::get(const std::string& name) {
    auto it = models.find(name);
    if (it != models.end()) return it->second;
    return nullptr;
}

ModelManager::~ModelManager() {
    for (auto& kv : models) {
        delete kv.second;
    }
    models.clear();
}

void ModelManager::createModels() {
    loadFromData(
        "sphere",
        std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(float)), 
        6, 3, 3
    );

    loadFromObj(
        "sphereWithUV", "sphere.obj"
    );

    loadFromData(
        "tree",
        std::vector<float>(tree, tree + sizeof(tree) / sizeof(float)), 
        6, 3, 3
    );
    
    loadFromData(
        "bush",
        std::vector<float>(bushes, bushes + sizeof(bushes) / sizeof(float)), 
        6, 3, 3
    );

    loadFromData(
        "plain",
        std::vector<float>(plain, plain + sizeof(plain) / sizeof(float)), 
        8, 3, 3, 2
    );

    loadFromData(
        "suzi",
        std::vector<float>(suziSmooth, suziSmooth + sizeof(suziSmooth) / sizeof(float)),
        6, 3, 3
    );

    loadFromObj(
        "fiona", "fiona.obj"
    );

    loadFromObj(
        "shrek", "shrek.obj"
    );

    loadFromObj(
        "toiled", "toiled.obj"
    );

    loadFromObj(
        "formula", "formula1.obj"
    );

    loadFromObj(
        "hamburger", "Hamburger_01.obj"
    );
}