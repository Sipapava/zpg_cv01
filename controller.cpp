#include "controller.h"
#include <stdio.h>
//Osetrit kdyz jeste nemame kameru podminky

Controller::Controller(Camera* camera) {
    this->rightMousePressed = false;
    this->camera = camera;
    lastX = 0;lastY = 0;
}
Controller::~Controller() {

}

bool Controller::setCamera(Camera* camera) {
    this->camera = camera;
    if (this->camera) {
        return true;
    }
    
}
void Controller::keyboardMovement(int key, int scancode, int action, int mods) {
   
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_W) {
            this->movementPressed[0] = true;
            
        }
        else if (key == GLFW_KEY_S) {
            this->movementPressed[1] = true;
        }
        else if (key == GLFW_KEY_D) {
            this->movementPressed[2] = true;
        }
        else if (key == GLFW_KEY_A) {
            this->movementPressed[3] = true;
        }
    }
    else if (action == GLFW_RELEASE) {
       
        for (int i = 0; i < 4; i++) {
            this->movementPressed[i] = false;
           
        }
    }
}
static bool firstMouse = true;

void Controller::mouseMovement(double xpos, double ypos) {
    

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
        return;
    }

    if (rightMousePressed) {
        double dx = xpos - lastX;
        double dy = ypos - lastY;  
        
        camera->adjustTarget(dx, dy);
    }

    lastX = xpos;
    lastY = ypos;
}

void Controller::mousePress(int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            rightMousePressed = true;
            
        }
        else if (action == GLFW_RELEASE) {
            rightMousePressed = false;
           
        }
    }
}

void Controller::Update() {
    
    for (int i = 0; i < 4; i++) {
        switch (i) {
        case 0:
            if (this->movementPressed[0]) camera->moveForward();
            break;
        case 1:
            if (this->movementPressed[1]) camera->moveBackward();
            break;
        case 2:
            if(this->movementPressed[2]) camera->moveRight();
            break;
        case 3:
            if (this->movementPressed[3]) camera->moveLeft();
            break;
        }
    }
};