#pragma once
#pragma once
#include <GL/glew.h>
#include <vector>

class Mesh {
public:
    Mesh(const std::vector<float>& vertices);
    void setupMesh();
    void draw();

private:
    GLuint VAO, VBO;
    std::vector<float> vertices;
};
