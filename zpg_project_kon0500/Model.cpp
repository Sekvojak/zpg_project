#include "Model.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <iostream>

Model::Model(const std::vector<float>& vertices, int stride, int positionSize, int normalSize)
    : vertices(vertices), VAO(0), VBO(0), stride(stride), positionSize(positionSize), normalSize(normalSize){}

Model::Model(const char* name)
{
    std::string inputfile = std::string("Assets/") + name;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str(), "Assets/");
    if (!warn.empty()) std::cout << "Warn: " << warn << std::endl;
    if (!err.empty()) std::cerr << "Err: " << err << std::endl;
    if (!ret) throw std::runtime_error("Failed to load OBJ file!");

    // Vyčistíme a naplníme členský vektor
    vertices.clear();

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            // Position
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);

            // Normals (if exist)
            if (index.normal_index >= 0) {
                vertices.push_back(attrib.normals[3 * index.normal_index + 0]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 1]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 2]);
            }
            else {
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }

            // UV coords (if exist)
            if (index.texcoord_index >= 0) {
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);
            }
            else {
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }
        }
    }

    stride = 8;          // 3 pozícia + 3 normála + 2 UV
    positionSize = 3;
    normalSize = 3;

    std::cout << "Loaded model " << name
        << " | vertices: " << attrib.vertices.size() / 3
        << " | normals: " << attrib.normals.size() / 3 << std::endl;


    setupMesh(); 
}


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
