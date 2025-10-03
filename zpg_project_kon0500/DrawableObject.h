#pragma once
#include <GL/glew.h>
#include "Model.h"
#include "ShaderProgram.h"
#include "AbstractTransformation.h"

class DrawableObject {
public:
    DrawableObject(Model* model, ShaderProgram* shader, AbstractTransformation* transformation = nullptr);
    void draw();
    AbstractTransformation* getTransformation();

private:
    Model* model;
    ShaderProgram* shader;
    AbstractTransformation* transformation;
};
