#include "app.h"
App::App() {
    controller = nullptr;
    modelManager = new ModelManager();
}

App::~App() {
    glfwSetWindowShouldClose(window, GLFW_TRUE);

    for (auto scene : scenes) {
        delete scene;
    }
    scenes.clear();
    delete controller;
    delete modelManager;

    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }
}

void App::createScene() {
    Scene* ss = new Scene(this->modelManager);
    scenes.push_back(ss);
}

bool App::prepareController() {
    controller = new Controller(scenes[sceneIndex]);
    return true;
}



void App::deleteScene(size_t index) {
    if (index < scenes.size()) {
        delete scenes[index];
        scenes.erase(scenes.begin() + index);
    }
}

Scene* App::getScene(size_t index) {
    if (index < scenes.size()) return scenes[index];
    return nullptr;
}

int App::getSceneIndex() {
    return sceneIndex;
}

bool App::initialize() {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return false;
    }

    window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "ERROR: could not start GLEW\n");
        return false;
    }

    
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // info o systému
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float)height; //ratio of display
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    return true;
}

void App::run(int sceneId) {
    if (!window || scenes.empty()) return;

   
    sceneIndex = sceneId;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

   

    

    while (window && !glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        controller->Update();

        
        Scene* scene = scenes[sceneIndex];
        
        scene->draw();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}



void App::error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}


void App::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (glfwGetWindowUserPointer(window)) {
        App* app = static_cast<App*>(glfwGetWindowUserPointer(window)); //returns general reference
        app->onKey(key, scancode, action, mods);
    }
}

void App::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    if (glfwGetWindowUserPointer(window)) {
        App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
        app->onMouseMove(xpos, ypos);
    }
}

void App::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (glfwGetWindowUserPointer(window)) {
        App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
        
        app->onMouseButton(button, action, mods);
    }
}

void App::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    if (glfwGetWindowUserPointer(window)) {
        App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
        app->onResize(width, height);
        
    }
}


void App::onResize(int width, int height) {
    
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
    controller->updateWindowSize(width, height);
}

void App::onKey(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }


    if (key == GLFW_KEY_H && action == GLFW_PRESS) {
        int count = static_cast<int>(scenes.size());
        sceneIndex++;
        if (sceneIndex >= count) {
            sceneIndex = 0;
        }
        this->controller->setScene(scenes[sceneIndex]);

    }
    else if (key == GLFW_KEY_J && action == GLFW_PRESS) {
        int count = static_cast<int>(scenes.size());
        sceneIndex--;
        if (sceneIndex < 0) {
            sceneIndex = count - 1;
        }
        this->controller->setScene(scenes[sceneIndex]);
    }
    else {
        controller->keyboardMovement(key, scancode, action, mods);
    }


}





void App::onMouseButton(int button, int action, int mods) {
    double xpos; double ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    controller->mousePress(button, action, mods,xpos,ypos);
}

void App::onMouseMove(double xpos, double ypos) {
   
    controller->mouseMovement(xpos, ypos);
   
}