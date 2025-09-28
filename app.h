#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "Scene.h"

class App {
private:
    std::vector<Scene*> scenes;
    GLFWwindow* window = nullptr;

public:
    App() = default;
    ~App();

    void addScene(Scene* scene);
    void deleteScene(size_t index);
    Scene* getScene(size_t index);

    bool initialize();
    void run(int sceneId);

private:
    static void error_callback(int error, const char* description);
};
