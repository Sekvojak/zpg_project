#pragma once
#include <GL/glew.h>
#include <vector>

class Mesh {
public:
    Mesh(const std::vector<float>& vertices, int stride, int positionSize, int colorSize);
    void setupMesh();
    void draw();

private:
    GLuint VAO, VBO;
    int stride;
    int positionSize;
    int colorSize;
    std::vector<float> vertices;
};
