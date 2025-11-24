#include <iostream>
#include "Application.h"

void Application::initialization() {
    if (!glfwInit()) exit(-1);

    glfwWindowHint(GLFW_STENCIL_BITS, 8);
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

    // object deleting
    if (glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS) {
        Scene* s = sceneManager.getActiveScene();
        s->deleteSelected();
    }

    // tree planting
    static bool tWasPressedLastFrame = false;
    int tState = glfwGetKey(window, GLFW_KEY_T);

    if (tState == GLFW_PRESS && !tWasPressedLastFrame) {
        Scene* s = sceneManager.getActiveScene();
        if (s) {
            s->plantTree(&modelManager, &shaderManager);
        }
    }

    tWasPressedLastFrame = (tState == GLFW_PRESS);

    // object movement
    Scene* s = sceneManager.getActiveScene();
    float speed = 0.2f;  

    if (s != nullptr) {
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            s->moveSelected(0.0f, -speed);   
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            s->moveSelected(0.0f, speed);    
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            s->moveSelected(-speed, 0.0f);   
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            s->moveSelected(speed, 0.0f);    
    }


    // scenes
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        sceneManager.setActiveScene(0);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        sceneManager.setActiveScene(1);
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        sceneManager.setActiveScene(2);
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        sceneManager.setActiveScene(3);
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        sceneManager.setActiveScene(4);
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
        sceneManager.setActiveScene(5);

        if (!shootingActive)
        {
            Scene* s6 = sceneManager.getActiveScene();

            Model* model = modelManager.get("shrek");
            ShaderProgram* shader = shaderManager.clone("phong");
            shader->setLightManager(s6->getLightManager());

            shooting = new ShootingRange(s6, model, shader);
            shooting->spawnTarget();
            shooting->spawnTarget();
            shooting->spawnTarget();

            shootingActive = true;

        }
    }
   
    }

void Application::createShaders() {
    shaderManager.createShaders(camera);
}

void Application::createModels() {
    modelManager.createModels();
}

void Application::setupScenes() {
    Scene* s1 = SceneFactory::createScene1(&shaderManager, &modelManager);
    Scene* s2 = SceneFactory::createScene2(&shaderManager, &modelManager);
    Scene* s3 = SceneFactory::createScene3(&shaderManager, &modelManager);
    Scene* s4 = SceneFactory::createScene4(&shaderManager, &modelManager);
    Scene* s5 = SceneFactory::createScene5(&shaderManager, &modelManager);
    Scene* s6 = SceneFactory::createScene6(&shaderManager, &modelManager);




    s1->getLightManager()->addLight(cameraController->getFlashlight());
    s2->getLightManager()->addLight(cameraController->getFlashlight());
    s3->getLightManager()->addLight(cameraController->getFlashlight());
    s4->getLightManager()->addLight(cameraController->getFlashlight());
    s5->getLightManager()->addLight(cameraController->getFlashlight());
    s6->getLightManager()->addLight(cameraController->getFlashlight());



    sceneManager.addScene(s1);
    sceneManager.addScene(s2);
    sceneManager.addScene(s3);
    sceneManager.addScene(s4);
    sceneManager.addScene(s5);
    sceneManager.addScene(s6);

}

void Application::handleLeftClick() {
    static bool leftMousePressedLastFrame = false;

    int leftState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

    if (leftState == GLFW_PRESS && !leftMousePressedLastFrame) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        Scene* activeScene = sceneManager.getActiveScene();
        if (activeScene) {
            activeScene->onClick(mouseX, mouseY, camera);

            if (shootingActive && shooting)
            {
                int id = activeScene->getSelectedObjectID();
                shooting->onClick(id);
            }

            }
        }

    leftMousePressedLastFrame = (leftState == GLFW_PRESS);
}


void Application::run() {
    glEnable(GL_DEPTH_TEST);
    setupScenes();

    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        double now = glfwGetTime();
        float dt = static_cast<float>(now - lastTime);
        lastTime = now;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        
        handleInput();
        int active = sceneManager.getActiveSceneIndex();

        if (active != 5) {
            cameraController->update(window, dt);
        }
        else {
            camera->setEyeFrontUp(
                glm::vec3(0.0f, 1.0f, 0.0f),   // pozícia kamery
                glm::vec3(0.0f, 0.0f, -1.0f),  // smer
                glm::vec3(0.0f, 1.0f, 0.0f)
            );
        }
        cameraController->processMouse(window);
        cameraController->checkResize(window);

        if (shootingActive && shooting)
            shooting->update(dt);


        sceneManager.updateActiveScene(dt);
        sceneManager.drawActiveScene();

        handleLeftClick();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // cleanup
    shaderManager.cleanup();

    glfwDestroyWindow(window);
    glfwTerminate();
}
