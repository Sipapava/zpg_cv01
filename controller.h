#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "camera.h"
class Controller {
private:
	bool rightMousePressed;
	bool movementPressed[4] = { false, false, false, false };
	double lastX; double lastY;
	Camera* camera;
	

public:
	Controller(Camera* camera);
	~Controller();
	void keyboardMovement(int key, int scancode, int action, int mods); 
	void mouseMovement(double xpos, double ypos);
	void mousePress(int button, int action, int mods);
	bool setCamera(Camera* camera);
	void Update();
};
