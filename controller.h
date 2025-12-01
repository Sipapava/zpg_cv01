#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "scene.h"
class Controller {
private:
	bool rightMousePressed;
	bool movementPressed[4] = { false, false, false, false };
	bool bezPressed;
	double lastX; double lastY;
	Scene* scene;
	std::vector<glm::vec3> points;
	

public:
	Controller(Scene* scene);
	~Controller();
	void keyboardMovement(int key, int scancode, int action, int mods); 
	void mouseMovement(double xpos, double ypos);
	void mousePress(int button, int action, int mods,double x, double y);
	bool setScene(Scene* scene);
	void Update();
	
};
