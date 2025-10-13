#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "controller.h"
#include "Scene.h"

class App {
private:
    std::vector<Scene*> scenes;
    GLFWwindow* window = nullptr;
    int sceneIndex = 0;
    Controller* controller;

public:
    App();
    ~App();

    void addScene(Scene* scene);
    void deleteScene(size_t index);
    Scene* getScene(size_t index);
    int getSceneIndex();

    bool initialize();
    void run(int sceneId);

    bool prepareController();
    

    void onKey(int key, int scancode, int action, int mods);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void onMouseButton(int button, int action, int mods);
    static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
    void onMouseMove(double xpos, double ypos);

private:
    static void error_callback(int error, const char* description);
};
