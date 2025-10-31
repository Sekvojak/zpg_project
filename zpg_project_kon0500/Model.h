#pragma once
#include <GL/glew.h>
#include <vector>

class Model {
public:
    Model(const std::vector<float>& vertices, int stride, int positionSize, int normalSize);
    Model(const char* name);
    void setupMesh();
    void bind();

private:
    GLuint VAO, VBO;
    int stride;
    int positionSize;
    int normalSize;
    std::vector<float> vertices;
};
