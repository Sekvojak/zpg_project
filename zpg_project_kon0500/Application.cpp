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

    camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, 800, 600);
    cameraController = new CameraController(camera);

}

void Application::handleInput() {   
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        sceneManager.setActiveScene(0);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        sceneManager.setActiveScene(1);
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        sceneManager.setActiveScene(2);
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        sceneManager.setActiveScene(3);
}

void Application::createShaders() {
    shaderManager.createShaders(camera);
}

void Application::run() {
    glEnable(GL_DEPTH_TEST);

    sceneManager.addScene(SceneFactory::createScene1(&shaderManager));
    sceneManager.addScene(SceneFactory::createScene2(&shaderManager));
    sceneManager.addScene(SceneFactory::createScene3(&shaderManager));
    sceneManager.addScene(SceneFactory::createScene4(&shaderManager));


    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        double now = glfwGetTime();
        float dt = static_cast<float>(now - lastTime);
        lastTime = now;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        handleInput();

        sceneManager.updateActiveScene(dt);
        sceneManager.drawActiveScene();

        cameraController->update(window, dt);
        cameraController->processMouse(window);
        cameraController->checkResize(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // cleanup
    shaderManager.cleanup();

    glfwDestroyWindow(window);
    glfwTerminate();
}
