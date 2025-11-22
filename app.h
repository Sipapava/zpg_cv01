#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "controller.h"
#include "Scene.h"
#include "modelManager.h"

class App {
private:
    std::vector<Scene*> scenes;
    ModelManager* modelManager;
    GLFWwindow* window = nullptr;
    int sceneIndex = 0;
    Controller* controller;

public:
    App();
    ~App();

    void createScene();
    void deleteScene(size_t index);
    Scene* getScene(size_t index);
    int getSceneIndex();

    bool initialize();
    void run(int sceneId);

    bool prepareController();
    

    void onKey(int key, int scancode, int action, int mods);
    void onMouseButton(int button, int action, int mods);
    void onMouseMove(double xpos, double ypos);
    void onResize(int width, int height);
    


private:
    static void error_callback(int error, const char* description);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
    static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};
