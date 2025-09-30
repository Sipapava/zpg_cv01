#include "app.h"

App::~App() {
    
    for (auto scene : scenes) {
        delete scene;
    }
    scenes.clear();

    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }
}

void App::addScene(Scene* scene) {
    scenes.push_back(scene);
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
    float ratio = width / (float)height; //ratio obrazovky
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    return true;
}

void App::run(int sceneId) {
    if (!window || scenes.empty()) return;

   
    Scene* scene = nullptr;
    for (auto s : scenes) {
        if (s->getId() == sceneId) {
            scene = s;
            break;
        }
    }

    if (!scene) {
        fprintf(stderr, "Scene with ID %d not found!\n", sceneId);
        return;
    }

    glEnable(GL_DEPTH_TEST);

    while (window && !glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        scene->draw();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}


void App::error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}
