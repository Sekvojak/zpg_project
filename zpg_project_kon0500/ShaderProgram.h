#pragma once
#include <GL/glew.h>

class ShaderProgram {
private:
    GLuint shaderProgram;

public:
    ShaderProgram(const char* vertexSrc, const char* fragmentSrc);
    void use();
};

