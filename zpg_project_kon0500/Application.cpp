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

    // bezier mode
    static bool bHeld = false;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
    {
        if (!bHeld)
        {
            Scene* activeS = sceneManager.getActiveScene();
            if (activeS)
            {
                DrawableObject* selected = activeS->getObjectByID(activeS->getSelectedObjectID());
                if (selected)
                {
                    bezierMode = !bezierMode;

                    if (bezierMode)
                    {
                        bezierPoints.clear();
                        std::cout << "Bezier mode entered\n";
                    }
                    else {
                        std::cout << "Bezier mode OFF\n";
                    }
                }
            }

            bHeld = true;
        }
    }
    else
    {
        bHeld = false;
    }


    // start Spline
    static bool enterHeld = false;
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        if (!enterHeld && bezierMode)
        {
            Scene* activeS = sceneManager.getActiveScene();
            if (activeS)
            {
                DrawableObject* selected = activeS->getObjectByID(activeS->getSelectedObjectID());

                if (selected && bezierPoints.size() >= 3)
                {   

                    glm::mat4 objectM = selected->computeModelMatrix();
                    glm::vec3 startPos = glm::vec3(objectM[3]);
                    std::cout << "computeModelMatrix pos = " << startPos.x << " " << startPos.y << " " << startPos.z << "\n";

                    std::vector<glm::vec3> controlPoints;
                    controlPoints.push_back(startPos);
                    for (auto& p : bezierPoints) {
                        controlPoints.push_back(p);
                    }


                    auto* spline = new TransformBezierSpline(controlPoints, bezierSpeed);

                    AbstractTransformation* originalT = selected->getTransformation();

                    TransformationComposite* comp = dynamic_cast<TransformationComposite*>(originalT);

                    if (!comp)
                    {
                        comp = new TransformationComposite();
                        
                        if (originalT)
                        {
                            comp->addChild(originalT);
                        }

                        selected->setTransformation(comp);

                    }
                    comp->removeAllTranslates();
                    comp->removeAllBezierSplines();
                    comp->addChildAtBeginning(spline);

                    std::cout << "Spline added\n";

                    bezierMode = false;
                    bezierPoints.clear();

                    
                }
            }
            enterHeld = false;
        }
    }
    else
    {
        enterHeld = false;
    }


    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        Scene* activeS = sceneManager.getActiveScene();
        for (auto* m : bezierMarkers)
            activeS->removeObject(m);

        bezierMarkers.clear();
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

        if (bezierMode)
        {
            int winX = (int)mouseX;
            int winY = camera->getHeight() - int(mouseY) - 1;

            float depth = 0.0f;
            glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
            glm::vec3 screenPos(winX, winY, depth);
            glm::vec4 viewport(0, 0, camera->getWidth(), camera->getHeight());

            glm::vec3 worldPos = glm::unProject(
                screenPos,
                camera->getViewMatrix(),
                camera->getProjectionMatrix(),
                viewport
            );

            bezierPoints.push_back(worldPos);

            // markers
            Model* sphere = modelManager.get("sphere"); 
            ShaderProgram* sh = shaderManager.clone("lambert");
            sh->setLightManager(activeScene->getLightManager());


            auto* markerTransform = new TransformationComposite();
            markerTransform->addChild(new TransformTranslate(worldPos));
            markerTransform->addChild(new TransformScale(glm::vec3(0.2f)));

            auto* marker = new DrawableObject(sphere, sh, markerTransform);
            marker->setColor(glm::vec3(1.0f, 0.2f, 0.2f)); 

            activeScene->addObject(marker);
            bezierMarkers.push_back(marker);


            std::cout << "Added point: "
                << worldPos.x << " "
                << worldPos.y << " "
                << worldPos.z << "\n";
        }
        else
        {
            if (activeScene) {
                activeScene->onClick(mouseX, mouseY, camera);

                if (shootingActive && shooting)
                {
                    int id = activeScene->getSelectedObjectID();
                    shooting->onClick(id);
                }
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
                glm::vec3(0.0f, 1.0f, 0.0f),   
                glm::vec3(0.0f, 0.0f, -1.0f),  
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
