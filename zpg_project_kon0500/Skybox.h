#pragma once
#include <GL/glew.h>
#include <array>
#include <string>
#include "ShaderProgram.h"

class Skybox {
public:
    Skybox(ShaderProgram* shader, const std::array<std::string, 6>& faces);
    ~Skybox();
    void draw();

private:
    GLuint vao, vbo, cubemapTex;
    ShaderProgram* shader;
};
