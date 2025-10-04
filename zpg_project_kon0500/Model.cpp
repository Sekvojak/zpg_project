#include "Model.h"

Model::Model(const std::vector<float>& vertices, int stride, int positionSize, int normalSize)
    : vertices(vertices), VAO(0), VBO(0), stride(stride), positionSize(positionSize), normalSize(normalSize){}

void Model::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, positionSize, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
    //(index , pocet , typ , normalized , posun , pocatek )
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, normalSize, GL_FLOAT, GL_TRUE, stride * sizeof(float), (void*)(positionSize * sizeof(float)));

    glBindVertexArray(0);


}

void Model::bind() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / stride);
    glBindVertexArray(0);
}
