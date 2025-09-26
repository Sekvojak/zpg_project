#include "Application.h"
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

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

}

void Application::createShaders() {
    const char* vertexShaderBasic = R"(
        #version 330 core
        layout(location = 0) in vec3 position;
        layout(location = 1) in vec3 color;
        out vec3 vColor;
        void main() {
            gl_Position = vec4(position, 1.0);
            vColor = color;
        })";

    const char* fragmentShaderBasic = R"(
        #version 330 core
        in vec3 vColor;
        out vec4 fragColor;
        void main() {
            fragColor = vec4(vColor, 1.0);
        })";

    shaders["basic"] = new ShaderProgram(vertexShaderBasic, fragmentShaderBasic);


    const char* vertexShaderTriangle = R"(
    #version 330 core
    layout(location = 0) in vec3 position;
    void main() {
        gl_Position = vec4(position, 1.0);
    })";

    const char* fragmentShaderTriangle = R"(
    #version 330 core
    out vec4 fragColor;
    void main() {
        fragColor = vec4(0.5, 0.0, 0.5, 1.0);
    })";
    
    shaders["triangle"] = new ShaderProgram(vertexShaderTriangle, fragmentShaderTriangle);

}

void Application::createModels() {
    // vertexy trojuholníka
    std::vector<float> triangle = {
        0.7f, 0.5f, 0.0f,
        0.6f, 0.3f, 0.0f,
        0.8f, 0.3f, 0.0f
    };


    std::vector<float> coloredSquare = {
   -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // žltá
   -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // červená
    0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // zelená

   -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // žltá
    0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // zelená
    0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f   // modrá
    };

    Mesh* triangleMesh = new Mesh(triangle, 3, 3, 0);
    triangleMesh->setupMesh(); //   //(index , pocet , typ , normalized , posun , pocatek )   
    
    Mesh* squareMesh = new Mesh(coloredSquare, 6, 3, 3);
    squareMesh->setupMesh();   //(index , pocet , typ , normalized , posun , pocatek ) -> 

    models.push_back(new Model(triangleMesh, shaders["triangle"]));
    models.push_back(new Model(squareMesh, shaders["basic"]));

}


void Application::run() {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
    

        // shader -> objekt -> vykreslit
        
        for (auto model : models) {
            model->draw();
        }

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
