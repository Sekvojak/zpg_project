#include <iostream>
#include "Application.h"




void Application::initialization() {
    if (!glfwInit()) exit(-1);

    window = glfwCreateWindow(800, 600, "ZPG", nullptr, nullptr);
    if (!window) { glfwTerminate(); exit(-1); }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        exit(-1);
    }

    glViewport(0, 0, 800, 600);

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

}

void Application::handleInput()
{
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        sceneManager.setActiveScene(0);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        sceneManager.setActiveScene(1);
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        sceneManager.setActiveScene(2);
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

    Shader vertexBasic (GL_VERTEX_SHADER, vertexShaderBasic);
    Shader fragmentBasic (GL_FRAGMENT_SHADER, fragmentShaderBasic);
    shaders["basic"] = new ShaderProgram(vertexBasic, fragmentBasic);


    const char* vertexShaderTriangle = R"(
    #version 330 core
    layout(location = 0) in vec3 position;
    uniform mat4 model;
    out vec4 pos;

    void main() {
        gl_Position = model * vec4(position, 1.0);
        pos = gl_Position;
    })";

    const char* fragmentShaderTriangle = R"(
    #version 330 core
    out vec4 fragColor;
    in vec4 pos;
    void main() {
        fragColor = vec4(0.7, 1.0, 0.5, 1.0);
    })";
    

    Shader vertexTriangle(GL_VERTEX_SHADER, vertexShaderTriangle);
    Shader fragmentTriangle(GL_FRAGMENT_SHADER, fragmentShaderTriangle);
    shaders["triangle"] = new ShaderProgram(vertexTriangle, fragmentTriangle);

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

    Shader vertexSphere(GL_VERTEX_SHADER, vertexShaderSphere);
    Shader fragmentSphere(GL_FRAGMENT_SHADER, fragmentShaderSphere);
    shaders["sphere"] = new ShaderProgram(vertexSphere, fragmentSphere);

}

void Application::run() {
    glEnable(GL_DEPTH_TEST);

    sceneManager.addScene(SceneFactory::createScene1(shaders));
    sceneManager.addScene(SceneFactory::createScene2(shaders));
    sceneManager.addScene(SceneFactory::createScene3(shaders));

    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {

        double now = glfwGetTime();
        float dt = static_cast<float>(now - lastTime);
        lastTime = now;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        handleInput();

        sceneManager.updateActiveScene(dt);
        sceneManager.drawActiveScene();
       
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // cleanup

    for (auto& pair : shaders)
        delete pair.second;

    glfwDestroyWindow(window);
    glfwTerminate();
}
