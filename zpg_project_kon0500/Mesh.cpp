#include "Mesh.h"

Mesh::Mesh(const std::vector<float>& vertices, int stride, int positionSize, int colorSize)
    : vertices(vertices), VAO(0), VBO(0), stride(stride), positionSize(positionSize), colorSize(colorSize){}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, positionSize, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
    //(index , pocet , typ , normalized , posun , pocatek )
    if (colorSize)
    {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, colorSize, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(positionSize * sizeof(float)));

    }
    
    glBindVertexArray(0);


}

void Mesh::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / stride);
    glBindVertexArray(0);
}
