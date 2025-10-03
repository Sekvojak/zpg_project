#include <iostream>
#include <vector>

#include "Application.h"
#include "Model.h"
#include "Models/sphere.h"

#include "TransformationComposite.h"
#include "TransformDynamicTranslate.h"
#include "TransformDynamicRotate.h"
#include "TransformTranslate.h"
#include "TransformScale.h"

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
        uniform mat4 model;
        void main() {
            gl_Position = model * vec4(position, 1.0);
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
    uniform mat4 model;

    void main() {
        gl_Position = model * vec4(position, 1.0);
    })";

    const char* fragmentShaderTriangle = R"(
    #version 330 core
    out vec4 fragColor;
    void main() {
        fragColor = vec4(1.0, 0.0, 0.0, 0.0);
    })";
    
    shaders["triangle"] = new ShaderProgram(vertexShaderTriangle, fragmentShaderTriangle);

    const char* vertexShaderSphere = R"(
    #version 330 core
    layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 normal;
    
    uniform mat4 model;

    out vec3 vNormal;

    void main() {
        gl_Position = model * vec4(position, 1.0);
        vNormal = normal;
    })";

    const char* fragmentShaderSphere = R"(
    #version 330 core
    in vec3 vNormal;
    out vec4 fragColor;

    void main() {
        fragColor = vec4(normalize(vNormal) * 0.5 + 0.5, 1.0); // posunutie do 0..1
    })";

    shaders["sphere"] = new ShaderProgram(vertexShaderSphere, fragmentShaderSphere);

}

void Application::createModels() {
    // vertexy trojuholníka
    std::vector<float> triangle = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };


    std::vector<float> coloredSquare = {
   -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // žltá
   -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // červená
    0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // zelená

   -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // žltá
    0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // zelená
    0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f   // modrá
    };

    Model* triangleModel = new Model(triangle, 3, 3, 0);
    triangleModel->setupMesh(); //   //(index , pocet , typ , normalized , posun , pocatek )   
    
    Model* squareModel = new Model(coloredSquare, 6, 3, 3);
    squareModel->setupMesh();   //(index , pocet , typ , normalized , posun , pocatek ) -> 

    Model* sphereModel = new Model(std::vector<float>(sphere, sphere + 17280), 6, 3, 3);
    sphereModel->setupMesh();

    /*
    DrawableObject* obj = new DrawableObject(sphereModel, shaders["sphere"]);
    // objects.push_back(obj);


    DrawableObject* obj2 = new DrawableObject(squareModel, shaders["basic"]);
    // objects.push_back(obj2);
    */
    auto* composite = new TransformationComposite();
    composite->addChild(new TransformScale(glm::vec3(0.5f, 0.5f, 0.5f)));
    composite->addChild(new TransformTranslate(glm::vec3(0.0f, 0.5f, 0.0f)));
    composite->addChild(new TransformDynamicRotate(45.0f,glm::vec3(0.0f, 0.0f, 1.0f)));
    composite->addChild(new TransformTranslate(glm::vec3(0.0f, -0.5f, 0.0f)));





    objects.push_back(new DrawableObject(triangleModel, shaders["triangle"], composite));

}

void Application::run() {
    glEnable(GL_DEPTH_TEST);
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {

        double now = glfwGetTime();
        float dt = static_cast<float>(now - lastTime);
        lastTime = now;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        // shader -> objekt -> vykreslit
        
        for (auto* object : objects) {
            object->getTransformation()->update(dt);
        }

        for (auto object : objects) {
            object->draw();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // cleanup
    for (auto model : models) {
        delete model;
    }

    for (auto& pair : shaders)
        delete pair.second;

    glfwDestroyWindow(window);
    glfwTerminate();
}
