#pragma once
#include <GL/glew.h>
#include "Mesh.h"
#include "ShaderProgram.h"

class Model {
public:
    Model(Mesh* mesh, ShaderProgram* shader);
    void draw();

private:
    Mesh* mesh;
    ShaderProgram* shader;
};
