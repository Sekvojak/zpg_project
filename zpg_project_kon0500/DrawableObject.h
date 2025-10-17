#pragma once
#include <GL/glew.h>
#include "Model.h"
#include "ShaderProgram.h"
#include "AbstractTransformation.h"

// AbstractTransformation premenovat na TransformComponent?

class DrawableObject {
public:
    ~DrawableObject();
    DrawableObject(Model* model, ShaderProgram* shader, AbstractTransformation* transformation = nullptr);
    void draw();
    AbstractTransformation* getTransformation();
    void setColor(const glm::vec3& color);

private:
    Model* model;
    ShaderProgram* shader;
    AbstractTransformation* transformation;
    glm::vec3 objectColor = glm::vec3(1.0f);
};
