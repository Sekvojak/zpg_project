#pragma once
#include <GL/glew.h>

class Shader {
public:
    GLuint shaderProgram;
    Shader(const char* vertexSrc, const char* fragmentSrc);
    void use();
};

