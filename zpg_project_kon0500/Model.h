#pragma once
#include <GL/glew.h>
#include <vector>

class Model {
public:
    Model(const std::vector<float>& vertices, int stride, int positionSize, int normalSize, int uvSize = 0);
    Model(const char* name);
    void setupMesh();
    void bind();

private:
    GLuint VAO, VBO;
    int stride;
    int positionSize;
    int normalSize;
    int uvSize;
    std::vector<float> vertices;
};
