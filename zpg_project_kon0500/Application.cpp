#include "Application.h"
#include "ShaderLoader.h"
#include "Mesh.h"
#include <iostream>
#include <vector>


void Application::initialization() {
    if (!glfwInit()) exit(-1);

    window = glfwCreateWindow(640, 480, "ZPG", nullptr, nullptr);
    if (!window) { glfwTerminate(); exit(-1); }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        exit(-1);
    }

    glViewport(0, 0, 640, 480);
}

void Application::createShaders() {
    std::string vertCode = loadShaderSource("shaders/basic.vert");
    std::string fragCode = loadShaderSource("shaders/basic.frag");
    shaders["basic"] = new Shader(vertCode.c_str(), fragCode.c_str());

}

void Application::createModels() {
    // vertexy trojuholníka
    std::vector<float> triangle = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f
    };

    std::vector<float> coloredSquare = {
   -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // žltá
   -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // červená
    0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // zelená

   -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // žltá
    0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // zelená
    0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f   // modrá
    };



    Mesh* mesh = new Mesh(triangle);
    mesh->setupMesh();
    
    Mesh* squareMesh = new Mesh(coloredSquare);
    squareMesh->setupMesh();

    meshes.push_back(mesh);
    meshes.push_back(squareMesh);
}

void Application::run() {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        shaders["basic"]->use();
        GLint aspectLoc = glGetUniformLocation(shaders["basic"]->shaderProgram, "aspect");
        glUniform1f(aspectLoc, 640.0f / 480.0f);



        for (auto mesh : meshes)
            mesh->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // cleanup
    for (auto mesh : meshes) {
        delete mesh;
    }

    for (auto& pair : shaders)
        delete pair.second;



    glfwDestroyWindow(window);
    glfwTerminate();
}
